#define NOMINMAX
#include <windows.h>
#include <d3d11.h>

#include "imgui_window.h"
#include "3rd-party/imgui/imgui.h"
#include "3rd-party/imgui/imgui_impl_win32.h"
#include "3rd-party/imgui/imgui_impl_dx11.h"

#include <thread>

#pragma comment(lib, "d3d11")

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace
{
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* device_context = nullptr;
	IDXGISwapChain* swap_chain = nullptr;
	ID3D11RenderTargetView* render_target_view = nullptr;
	bool swap_chain_occluded = false;
	UINT resize_width = 0;
	UINT resize_height = 0;

	void create_render_target()
	{
		ID3D11Texture2D* back_buffer = nullptr;
		swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
		device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
		back_buffer->Release();
	}

	void cleanup_render_target()
	{
		if (render_target_view) { render_target_view->Release(); render_target_view = nullptr; }
	}

	bool create_device(HWND hwnd)
	{
		DXGI_SWAP_CHAIN_DESC desc = {};
		desc.BufferCount = 2;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.OutputWindow = hwnd;
		desc.SampleDesc.Count = 1;
		desc.Windowed = TRUE;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		D3D_FEATURE_LEVEL feature_level;
		const D3D_FEATURE_LEVEL feature_levels[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0 };
		HRESULT result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, feature_levels, 2, D3D11_SDK_VERSION, &desc, &swap_chain, &device, &feature_level, &device_context);
		if (result == DXGI_ERROR_UNSUPPORTED)
		{
			result = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, feature_levels, 2, D3D11_SDK_VERSION, &desc, &swap_chain, &device, &feature_level, &device_context);
		}
		if (result != S_OK)
		{
			return false;
		}

		create_render_target();
		return true;
	}

	void cleanup_device()
	{
		cleanup_render_target();
		if (swap_chain) { swap_chain->Release(); swap_chain = nullptr; }
		if (device_context) { device_context->Release(); device_context = nullptr; }
		if (device) { device->Release(); device = nullptr; }
	}

	LRESULT WINAPI window_procedure(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		{
			return true;
		}

		switch (msg)
		{
			case WM_SIZE:
				if (wparam != SIZE_MINIMIZED)
				{
					resize_width = (UINT)LOWORD(lparam);
					resize_height = (UINT)HIWORD(lparam);
				}
				return 0;

			case WM_SYSCOMMAND:
				if ((wparam & 0xfff0) == SC_KEYMENU)
				{
					return 0;
				}
				break;

			case WM_DESTROY:
				PostQuitMessage(0);
				return 0;
		}
		return DefWindowProcW(hwnd, msg, wparam, lparam);
	}

	void run_imgui_window()
	{
		WNDCLASSEXW window_class = {};
		window_class.cbSize = sizeof(window_class);
		window_class.style = CS_CLASSDC;
		window_class.lpfnWndProc = window_procedure;
		window_class.hInstance = GetModuleHandleW(nullptr);
		window_class.hCursor = LoadCursor(nullptr, IDC_ARROW);
		window_class.lpszClassName = L"kuku_imgui";
		RegisterClassExW(&window_class);

		HWND hwnd = CreateWindowW(window_class.lpszClassName, L"kuku", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, nullptr, nullptr, window_class.hInstance, nullptr);

		if (!create_device(hwnd))
		{
			cleanup_device();
			DestroyWindow(hwnd);
			UnregisterClassW(window_class.lpszClassName, window_class.hInstance);
			return;
		}

		ShowWindow(hwnd, SW_SHOWDEFAULT);
		UpdateWindow(hwnd);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(device, device_context);

		const float clear_color[4] = { 0.12f, 0.12f, 0.12f, 1.0f };

		bool done = false;
		while (!done)
		{
			MSG msg;
			while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
				if (msg.message == WM_QUIT)
				{
					done = true;
				}
			}
			if (done)
			{
				break;
			}

			if (swap_chain_occluded && swap_chain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
			{
				Sleep(10);
				continue;
			}
			swap_chain_occluded = false;

			if (resize_width != 0 && resize_height != 0)
			{
				cleanup_render_target();
				swap_chain->ResizeBuffers(0, resize_width, resize_height, DXGI_FORMAT_UNKNOWN, 0);
				resize_width = resize_height = 0;
				create_render_target();
			}

			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();

			ImGui::Begin("kuku");
			ImGui::Text("Hello from kuku");
			ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
			ImGui::End();

			ImGui::Render();
			device_context->OMSetRenderTargets(1, &render_target_view, nullptr);
			device_context->ClearRenderTargetView(render_target_view, clear_color);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

			HRESULT result = swap_chain->Present(1, 0);
			swap_chain_occluded = (result == DXGI_STATUS_OCCLUDED);
		}

		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		cleanup_device();
		DestroyWindow(hwnd);
		UnregisterClassW(window_class.lpszClassName, window_class.hInstance);
	}
}

void start_imgui_window()
{
	std::thread(run_imgui_window).detach();
}


#pragma once

#include <stack>
#include "stack.h"
#include "call_frame.h"

class virtual_machine;

class rt::function;

class routine
{
public:
	routine(virtual_machine& vm, rt::function& function);

	virtual_machine& vm;

	stack stack;

	std::stack<call_frame> up_frames;
	call_frame call_frame;

	cell* top;

	inline void push(cell value) { *top++ = value; }
	inline cell pop() { return *--top; }

	bool running;

	void run();
	void stop();
	void perform_instruction();

	void push_call_frame(rt::function& function, cell* frame_start);
	void pop_call_frame();

	//template<typename T>
	//inline T read()
	//{
	//	auto result = *reinterpret_cast<T*>(ip);
	//	ip += sizeof(T);
	//	return result;
	//}
};
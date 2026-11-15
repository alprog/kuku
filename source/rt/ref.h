#pragma once

#include <vector>
#include <cstdint>

namespace rt
{
	class user_class;
	class property;
	class function;

	template <typename T>
	class ref
	{
	public:
		static constexpr uint16_t invalid_index = 0xFFFF;

		ref() = default;
		explicit ref(uint16_t index)
			: index{ index }
		{
		}

		T& operator*() const { return (*storage)[index]; }
		T* operator->() const { return &(*storage)[index]; }

		uint16_t get_index() const { return index; }
		bool is_valid() const { return index != invalid_index; }

		bool operator==(const ref&) const = default;

		static inline std::vector<T>* storage = nullptr;

	private:
		uint16_t index = invalid_index;
	};

	using type_ref = ref<rt::user_class>;
	using property_ref = ref<rt::property>;
	using function_ref = ref<rt::function>;
}

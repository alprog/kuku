#pragma once

#include "rt/function.h"
#include "instruction_mode.h"

union cell;

struct call_frame
{
	explicit call_frame(rt::function& function, cell* stack);
	
	rt::function* function;
	byte* ip;
	
	union
	{
		struct
		{
			cell* stack;
			cell* constants;
		};
		cell* ptr[2];
	};

	template <instruction_mode MODE>
	inline cell& get_cell(uint8_t index);

	template<>
	inline cell& get_cell<instruction_mode::R>(uint8_t index)
	{
		return stack[index];
	}

	template<>
	inline cell& get_cell<instruction_mode::K>(uint8_t index)
	{
		return function->constant_buffer[index];
	}
};
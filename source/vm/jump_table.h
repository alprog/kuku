#pragma once

#include "instruction_info.h"

class routine;

constexpr size_t INSTRUCTION_COUNT = 256;

using execute_function_ptr = void(*)(routine&);
using get_size_function_ptr = size_t(*)();
using get_info_function_ptr = instruction_info*(*)();

struct jump_table
{
	static execute_function_ptr execute_function[INSTRUCTION_COUNT];
	static get_size_function_ptr get_size_function[INSTRUCTION_COUNT];
	static get_info_function_ptr get_info_function[INSTRUCTION_COUNT];
	static void init();
};

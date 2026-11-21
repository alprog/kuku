
#pragma once

#include <vector>
#include "opcode.h"
#include "instruction_arg.h"

struct instruction_info
{
	opcode base_code;
	std::string comment;
	std::vector<instruction_arg> arguments;

	int get_argument_value(byte* ptr, const std::string& name) const;
	std::string to_string(byte* ptr) const;
};

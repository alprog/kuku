
#pragma once

#include <vector>
#include "opcode.h"
#include "instruction_arg.h"

struct instruction_info
{
	opcode base_code;
	std::string comment;
	std::vector<instruction_arg_meta_base*> arguments;

	std::string to_string(byte* ptr) const;
};

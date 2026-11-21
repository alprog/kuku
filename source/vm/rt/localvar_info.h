#pragma once

#include <string>
#include "vm/type_index.h"

namespace rt
{
	struct localvar_info
	{
		std::u16string name;
		type_index type_index;
		int stack_offset;
		int start_instruction;
		int end_instruction;
	};
}
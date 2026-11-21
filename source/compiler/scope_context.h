#pragma once

#include <vector>
#include "scope_type.h"

struct scope_context
{
	scope_context(scope_type scope_type, int start_place, int stack_size)
		: scope_type{ scope_type }
		, start_place{ start_place }
		, local_stack_size{ stack_size }
	{
	}

	scope_type scope_type;
	int start_place;
	int local_stack_size;
	std::vector<int> jump_to_end_places;
};
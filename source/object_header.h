
#pragma once

#include <core/types.h>
#include <vector>
#include "core/guid.h"
#include "cell.h"

struct object_header
{
	object_header(class_index class_index);
	void destroy();

	guid get_guid() const;

	byte packed_guid[6];
	class_index class_index;
	cell* data;
};

static_assert(sizeof(object_header) == 16);
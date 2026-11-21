
#include "object_header.h"

object_header::object_header(::class_index class_index)
	: class_index { class_index }
	, packed_guid { 0 }
{
	data = new cell[10];
}

void object_header::destroy()
{
	class_index = 0;
	if (data != nullptr)
	{
		delete data;
	}
}

guid object_header::get_guid() const
{
	return *reinterpret_cast<const guid*>(packed_guid);
}
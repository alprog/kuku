
#include "object_storage.h"

object_storage::object_storage(virtual_machine& vm)
	: vm { vm }
{
}

object_header& object_storage::get_object(object_index object_index)
{
	return objects[object_index];
}

object_index object_storage::create_object(class_index class_index)
{
	if (holes.empty())
	{
		objects.emplace_back(class_index);
		return objects.size() - 1;
	}
	else
	{
		object_index index = holes.top();
		holes.pop();
		new (&objects[index]) object_header(class_index); // placement new
		return index;
	}
}

void object_storage::destroy_object(object_index object_index)
{
	objects[object_index].destroy();
	holes.push(object_index);
}
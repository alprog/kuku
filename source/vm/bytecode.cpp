
#include "bytecode.h"

byte* bytecode::get_start_pointer()
{
	return bytes.data();
}

byte* bytecode::get_end_pointer()
{
	return bytes.data() + bytes.size();
}

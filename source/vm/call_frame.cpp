#include "call_frame.h"

call_frame::call_frame(rt::function& function, cell* stack)
	: function { &function }
	, stack { stack }
{
	ip = function.bytecode.get_start_pointer();
}
#pragma once

#include "rt/function.h"

union cell;

struct call_frame
{
	explicit call_frame(rt::function& function, cell* stack);
	
	rt::function* function;
	byte* ip;
	
	cell* stack;
};
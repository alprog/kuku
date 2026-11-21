#pragma once

#include "vm/rt/function.h"

class chunk
{
public:
	std::vector<rt::function> functions;
};
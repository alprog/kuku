
#pragma once

#include "symbol.h"

class type_symbol;

class field_symbol : public symbol
{
	type_symbol* type;
};

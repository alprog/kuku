
#pragma once

#include "symbol.h"

class type_symbol;

class variable_symbol : public symbol
{
public:
	using symbol::symbol;

	type_symbol* type;
};

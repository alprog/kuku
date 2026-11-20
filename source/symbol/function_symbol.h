
#pragma once

#include "symbol/symbol.h"
#include "symbol/variable_symbol.h"
#include <vector>

class type_symbol;

class function_symbol : public symbol
{
public:
	using symbol::symbol;

	type_symbol* result_type;
	std::vector<type_symbol*> arguments_types;

};

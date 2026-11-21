
#pragma once

#include <vector>
#include "compiler/symbol/symbol.h"
#include "compiler/symbol/field_symbol.h"
#include "compiler/symbol/function_symbol.h"

class type_symbol : public symbol
{
public:
	using symbol::symbol;

	type_symbol* parent_type;

	std::vector<field_symbol*> fields;
	std::vector<function_symbol*> functions;
};

#pragma once

#include <string>
#include <vector>
#include "compiler/statement_scope.h"
#include "compiler/symbol_type.h"

class symbol_reference;

class symbol
{
public:
	symbol(symbol_reference& definition);
	virtual ~symbol();

	std::u16string name;

	// debug info
	symbol_reference* definition;
	std::vector<symbol_reference*> usages;
	int stack_offset = -1;
};

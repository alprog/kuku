#pragma once

#include <vector>
#include "rt/user_class.h"
#include "symbol_table.h"

class type_registry
{
public:
	type_registry();

	rt::user_class& get_class(std::string name);

	std::vector<rt::user_class> classes;
	std::vector<rt::property> properties;
	std::vector<rt::function> functions;

	symbol_table symbol_table;
};
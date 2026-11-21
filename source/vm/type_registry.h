#pragma once

#include <vector>
#include "vm/rt/user_class.h"
#include "symbol_table.h"

class type_registry
{
public:
	type_registry();

	rt::user_class& get_class(std::string name);
	rt::property& get_property(rt::user_class& owner, const std::string& identity, std::string type);
	rt::function& get_function(rt::user_class& owner, const std::string& identity, std::vector<std::string> params, std::string result);

	std::vector<rt::user_class> classes;
	std::vector<rt::property> properties;
	std::vector<rt::function> functions;

	symbol_table symbol_table;
};
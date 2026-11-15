#pragma once

#include <vector>
#include "rt/user_class.h"

class type_registry
{
public:
	rt::user_class& register_class(std::string name);

	std::vector<rt::user_class> classes;
	std::vector<rt::property> properties;
	std::vector<rt::function> functions;
};
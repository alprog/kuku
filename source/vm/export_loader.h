#pragma once

#include <string>
#include <string_view>
#include "type_registry.h"

class export_loader
{
public:
	explicit export_loader(type_registry& registry);

	void load_test();
	void load(std::string_view text);

private:
	void load_line(std::string_view line);
	void load_member(std::string_view line);
	void load_property(const std::string& identity, const std::string& type);
	void load_function(const std::string& identity, const std::string& type);

	type_registry& registry;
	rt::user_class* current_class = nullptr;
};

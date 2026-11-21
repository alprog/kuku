#pragma once

#include <string>

class translation_module;

class export_creator
{
public:
	explicit export_creator(translation_module& module);

	std::string create();

private:
	translation_module& module;
};


#pragma once

#include <vector>
#include "compiler/stmt/statement.h"

class translation_module;

class semantic_analyzer
{
public:
	semantic_analyzer(translation_module& module);
	void analyze();

private:
	translation_module& module;
};
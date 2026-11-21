
#include "translation_module.h"
#include "semantic_analyzer.h"

semantic_analyzer::semantic_analyzer(translation_module& module)
	: module { module }
{
}

void semantic_analyzer::analyze()
{
	for (auto& statement : module.statements)
	{
		if (statement->is_valid)
		{
			statement->semantic_analyze();
		}
	}
}
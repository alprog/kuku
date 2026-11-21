#include "export_creator.h"

#include "translation_module.h"
#include "compiler/stmt/all.h"
#include "core/unicode/unicode.h"

static std::string to_string(const std::u16string& text)
{
	auto utf8 = unicode::to_utf8(text);
	return std::string(utf8.begin(), utf8.end());
}

export_creator::export_creator(translation_module& module)
	: module{ module }
{
}

std::string export_creator::create()
{
	std::string result;

	for (auto statement : module.statements)
	{
		if (!statement->is_valid)
		{
			continue;
		}

		if (auto class_statement = dynamic_cast<stmt::class_statement*>(statement))
		{
			result += to_string(class_statement->symbol->name) + "\n";
		}
		else if (auto function_statement = dynamic_cast<stmt::function_statement*>(statement))
		{
			if (function_statement->get_scope()->type == scope_type::class_body)
			{
				result += "." + to_string(function_statement->symbol->name) + "()\n";
			}
		}
	}

	return result;
}

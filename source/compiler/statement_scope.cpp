
#include "statement_scope.h"
#include "compiler/stmt/statement.h"
#include "compiler/symbol/symbol.h"

statement_scope::statement_scope(stmt::statement* statement, scope_type type)
	: statement{ statement }
	, type{ type }
{
}

bool statement_scope::is_root()
{
	return statement == nullptr;
}

statement_scope* statement_scope::get_parent()
{
	if (is_root())
	{
		return this;
	}
	else
	{
		return statement->get_scope();
	}
}

void statement_scope::define_symbol(symbol* symbol)
{
	if (symbol)
	{
		symbols.push_back(symbol);
	}
}

symbol* statement_scope::find_symbol(std::u16string name, int requesting_statement_sequence_number)
{
	for (int i = symbols.size() - 1; i >= 0; --i)
	{
		auto symbol = symbols[i];
		if (symbol->definition->token->statement->sequence_number < requesting_statement_sequence_number)
		{
			if (symbol->name == name)
			{
				return symbol;
			}
		}
	}

	if (is_root())
	{
		return nullptr;
	}
	else
	{
		return get_parent()->find_symbol(name, requesting_statement_sequence_number);
	}
}

void statement_scope::clear()
{
	symbols.clear();
}
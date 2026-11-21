
#pragma once

#include <vector>
#include "scope_type.h"
#include "core/types.h"

class symbol;

namespace stmt
{
	class statement;
}

class statement_scope
{
public:
	statement_scope(stmt::statement* statement, scope_type type);

	bool is_root();
	statement_scope* get_parent();

	void define_symbol(symbol* symbol);
	symbol* find_symbol(std::u16string name, int requesting_statement_sequence_number);
	void clear();

	scope_type type;
	std::vector<symbol*> symbols;
	stmt::statement* statement;
};
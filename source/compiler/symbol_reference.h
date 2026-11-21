
#pragma once

struct token;
class symbol;

namespace stmt
{
	class statement;
}

class symbol_reference
{
public:
	symbol_reference();
	void semantic_analyze(stmt::statement& statement);

	token* token;
	symbol* symbol;
};
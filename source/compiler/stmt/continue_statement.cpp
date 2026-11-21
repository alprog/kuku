#include "continue_statement.h"
#include "compiler/ast/integer_literal.h"
#include "compiler/compiler.h"

void stmt::continue_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_continue);
	if (parser.current->type == token_type::integer_literal)
	{
		level = ast::integer_literal(*parser.current).value;
		parser.next();
	}
}

void stmt::continue_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}
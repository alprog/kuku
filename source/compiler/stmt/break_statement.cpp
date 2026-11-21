#include "break_statement.h"

#include "compiler/compiler.h"
#include "compiler/ast/integer_literal.h"

void stmt::break_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_break);
	if (parser.current->type == token_type::integer_literal)
	{
		level = ast::integer_literal(*parser.current).value;
		parser.next();
	}
}

void stmt::break_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}
#include "else_statement.h"

#include "compiler/compiler.h"

void stmt::else_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_else);
}

void stmt::else_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}

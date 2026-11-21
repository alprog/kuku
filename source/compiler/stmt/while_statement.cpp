#include "while_statement.h"

#include "compiler/compiler.h"

void stmt::while_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_while);
	condition = parser.parse_expression();
	parser.require(token_type::keyword_do);
}

void stmt::while_statement::semantic_analyze()
{
	condition->semantic_analyze(*this);
}

void stmt::while_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}

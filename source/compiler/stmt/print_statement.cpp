#include "print_statement.h"

#include "compiler/compiler.h"

void stmt::print_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_print);
	expression = parser.parse_expression();
}

void stmt::print_statement::semantic_analyze()
{
    expression->semantic_analyze(*this);
}

void stmt::print_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}
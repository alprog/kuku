#include "function_statement.h"

#include "compiler/compiler.h"

void stmt::function_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_function);
	parse_symbol(parser);
	parser.require(token_type::open_parenthesis);
	// arguments
	parser.require(token_type::close_parenthesis);

	CHECK_END_OF_STATEMENT

	parser.require(token_type::colon);
	parser.require(token_type::identifier);
}

void stmt::function_statement::define_symbols(statement_scope* scope)
{
	scope->define_symbol(symbol);
}

void stmt::function_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}
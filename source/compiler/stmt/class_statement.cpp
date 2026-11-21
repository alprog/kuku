
#include "class_statement.h"
#include "compiler/symbol_reference.h"
#include "compiler/compiler.h"

void stmt::class_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_class);
	parse_symbol(parser);
}

void stmt::class_statement::define_symbols(statement_scope* scope)
{
	scope->define_symbol(symbol);
}

void stmt::class_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}
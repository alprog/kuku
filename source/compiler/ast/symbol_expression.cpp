
#include "symbol_expression.h"
#include "compiler/symbol/variable_symbol.h"
#include "compiler/compiler.h"

ast::symbol_expression::symbol_expression(token& token)
{
	reference.token = &token;
}

void ast::symbol_expression::semantic_analyze(stmt::statement& statement)
{
	reference.semantic_analyze(statement);
}

void ast::symbol_expression::compile(compiler& compiler)
{
	compiler.compile(*this);
}
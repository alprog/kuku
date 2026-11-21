
#include "expression_statement.h"

#include "compiler/ast/expression.h"
#include "compiler/compiler.h"

stmt::expression_statement::expression_statement(std::unique_ptr<ast::expression> expression)
	: expression{ std::move(expression) }
{
}

void stmt::expression_statement::parse_internal(parser& parser)
{
	return;
}

void stmt::expression_statement::semantic_analyze()
{
	expression->semantic_analyze(*this);
}

void stmt::expression_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}
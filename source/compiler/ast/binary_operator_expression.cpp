
#include "binary_operator_expression.h"
#include "compiler/compiler.h"

ast::binary_operator_expression::binary_operator_expression(std::unique_ptr<expression> left, binary_operator& op, std::unique_ptr<expression> right)
	: left{ std::move(left) }
	, op{ op }
	, right{ std::move(right) }
{
}

void ast::binary_operator_expression::semantic_analyze(stmt::statement& statement)
{
	left->semantic_analyze(statement);
	right->semantic_analyze(statement);

	/* TODO: analyze is it applicable to do operation */
}

void ast::binary_operator_expression::compile(compiler& compiler)
{
	compiler.compile(*this);
}
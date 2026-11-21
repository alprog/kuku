#include "loop_statement.h"

#include "compiler/compiler.h"

void stmt::loop_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_loop);
	CHECK_END_OF_STATEMENT

	parser.require(token_type::keyword_while);
	condition = parser.parse_expression();
}

void stmt::loop_statement::semantic_analyze()
{
	if (condition)
	{
		condition->semantic_analyze(*this);
	}
}

void stmt::loop_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}

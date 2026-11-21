
#include "end_statement.h"

#include "compiler/compiler.h"

void stmt::end_statement::parse_internal(parser& parser)
{
	parser.require(token_type::keyword_end);
}

void stmt::end_statement::compile(compiler& compiler)
{
	compiler.compile(*this);
}

#include "string_literal.h"
#include "compiler/compiler.h"

ast::string_literal::string_literal(token& token)
	: value{ token.get_source_text() }
{
	value.try_shrink();
}

void ast::string_literal::compile(compiler& compiler)
{
	compiler.compile(*this);
}
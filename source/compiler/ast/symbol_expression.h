
#pragma once

#include "expression.h"
#include "compiler/token.h"

namespace ast
{
	class symbol_expression : public expression
	{
	public:
		symbol_expression(token& token);
		virtual void semantic_analyze(stmt::statement& statement) override;
		virtual void compile(compiler& compiler) override;

		symbol_reference reference;
	};
}

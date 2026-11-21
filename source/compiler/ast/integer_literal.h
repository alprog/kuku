
#pragma once

#include "expression.h"
#include "compiler/token.h"

namespace ast
{
	class integer_literal : public expression
	{
	public:
		integer_literal(token& token);
		virtual void compile(compiler& compiler) override;

		integer value;
	};
}

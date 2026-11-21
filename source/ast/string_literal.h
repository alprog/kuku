
#pragma once

#include "expression.h"
#include "Token.h"
#include "vm/kuku/string.h"

namespace ast
{
	class string_literal : public expression
	{
	public:
		string_literal(token& token);
		virtual void compile(compiler& compiler) override;

		kuku::string value;
	};
}

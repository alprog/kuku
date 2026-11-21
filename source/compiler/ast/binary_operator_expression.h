
#pragma once

#include <memory>
#include "expression.h"
#include "compiler/binary_operator.h"

namespace ast
{
	class binary_operator_expression : public expression
	{
	public:
		binary_operator_expression(std::unique_ptr<expression> left, binary_operator& op, std::unique_ptr<expression> right);

		std::unique_ptr<expression> left;
		binary_operator& op;
		std::unique_ptr<expression> right;

		virtual void semantic_analyze(stmt::statement& statement) override;
		virtual void compile(compiler& compiler) override;
	};
}

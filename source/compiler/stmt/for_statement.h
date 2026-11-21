#pragma once

#include "statement.h"
#include "scoped_symboled_statement.h"
#include "compiler/symbol/variable_symbol.h"
#include "compiler/ast/expression.h"

namespace stmt
{
	class for_statement : public scoped_symboled_statement<scope_type::loop_body, variable_symbol>
	{
	public:
		virtual std::u16string get_statement_type() const override { return u"for_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }

		virtual void parse_internal(parser& parser) override;
		virtual void semantic_analyze() override;
		virtual void compile(compiler& compiler) override;

		std::unique_ptr<ast::expression> start_expression;
		std::unique_ptr<ast::expression> end_expression;
	};
}

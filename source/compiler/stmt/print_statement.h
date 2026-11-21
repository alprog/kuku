#pragma once

#include "statement.h"
#include "compiler/ast/expression.h"

namespace stmt
{
	class print_statement : public statement
	{
	public:
		virtual std::u16string get_statement_type() const override { return u"print_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }
	
		virtual void parse_internal(parser& parser) override;
		virtual void semantic_analyze() override;
		virtual void compile(compiler& compiler) override;

		std::unique_ptr<ast::expression> expression;
	};
}

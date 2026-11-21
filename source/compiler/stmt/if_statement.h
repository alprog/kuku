#pragma once

#include "scoped_statement.h"
#include "compiler/ast/expression.h"

namespace stmt
{
	class if_statement : public scoped_statement<scope_type::block_body>
	{
	public:
		virtual std::u16string get_statement_type() const override { return u"if_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }

		virtual void parse_internal(parser& parser) override;
		virtual void semantic_analyze() override;
		virtual void compile(compiler& compiler) override;

		std::unique_ptr<ast::expression> condition;
	};
}

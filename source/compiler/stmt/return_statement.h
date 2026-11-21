#pragma once

#include "statement.h"
#include "compiler/ast/expression.h"

namespace stmt
{
	class return_statement : public statement
	{
	public:
		virtual std::u16string get_statement_type() const override { return u"return_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }
		
	protected:
		virtual void parse_internal(parser& parser) override;

		std::unique_ptr<ast::expression> expression;
	};
}

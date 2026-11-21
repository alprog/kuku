
#pragma once

#include "statement.h"
#include "compiler/parser.h"
#include "symboled_statement.h"
#include "compiler/symbol/variable_symbol.h"

namespace stmt
{
	class variable_declaration_statement : public symboled_statement<variable_symbol>
	{
	public:
		virtual std::u16string get_statement_type() const override { return u"variable_declaration_statement"; }
		
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }

		virtual void parse_internal(parser& parser) override;
		virtual void semantic_analyze() override;
		virtual void define_symbols(statement_scope* scope) override;
		virtual void compile(compiler& compiler) override;

		std::unique_ptr<ast::expression> expression;
	};
}

#pragma once

#include "scoped_symboled_statement.h"
#include "compiler/symbol/function_symbol.h"

class compiler;

namespace stmt
{
	class function_statement : public scoped_symboled_statement<scope_type::function_body, function_symbol>
	{
	public:
		virtual std::u16string get_statement_type() const override { return u"function_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::class_body | scope_type::module_root; }
		
		virtual void define_symbols(statement_scope* scope) override;

	protected:
		virtual void parse_internal(parser& parser) override;
		virtual void compile(compiler& compiler) override;
	};
}

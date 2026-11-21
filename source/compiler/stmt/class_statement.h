
#pragma once

#include "scoped_symboled_statement.h"
#include "compiler/symbol/type_symbol.h"

namespace stmt
{
	class class_statement : public scoped_symboled_statement<scope_type::class_body, type_symbol>
	{
	public:
		virtual std::u16string get_statement_type() const override { return u"class_statement"; }
		virtual scope_type get_allowed_scopes() const override { return scope_type::module_root; }

	protected:
		virtual void parse_internal(parser& parser) override;
		virtual void define_symbols(statement_scope* scope) override;
		virtual void compile(compiler& compiler) override;
	};
}

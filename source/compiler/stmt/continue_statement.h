#pragma once

#include "statement.h"

class compiler;

namespace stmt
{
	class continue_statement : public statement
	{
		virtual std::u16string get_statement_type() const override { return u"continue_statement"; }

	public:
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }

	protected:
		virtual void parse_internal(parser& parser) override;
		virtual void compile(compiler& compiler) override;

	public:
		int level = 1;
	};
}

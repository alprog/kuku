
#pragma once

#include "stmt/statement.h"
#include "core/unexepected_error.h"

namespace stmt
{
	class unknown_statement : public stmt::statement
	{
		virtual std::u16string get_statement_type() const override { return u"unknown_statement"; }

		virtual scope_type get_allowed_scopes() const override { return scope_type::any; }

		virtual void parse_internal(parser& parser) override
		{
			throw unexpected_error();
		}
	};
}

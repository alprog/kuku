
#pragma once

#include "scoped_statement.h"

namespace stmt
{
	class block_statement : public scoped_statement<scope_type::block_body>
	{
		virtual std::u16string get_statement_type() const override { return u"block_statement"; }
		
	public:
		virtual scope_type get_allowed_scopes() const override { return scope_type::imperative_scopes; }
	};
}

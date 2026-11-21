
#pragma once

#include "compiler/stmt/statement.h"
#include "compiler/statement_scope.h"

namespace stmt
{
	class scoped_statement_base : public virtual stmt::statement
	{
	public:
		scoped_statement_base(scope_type scope_type)
			: inner_scope(this, scope_type)
		{
		}

		statement_scope inner_scope;
	};

	template <scope_type ScopeType>
	class scoped_statement : public stmt::scoped_statement_base
	{
	public:
		scoped_statement()
			: scoped_statement_base(ScopeType)
		{
		}
	};
}

#pragma once

#include "compiler/stmt/scoped_statement.h"
#include "compiler/stmt/symboled_statement.h"

namespace stmt
{
	template <scope_type ScopeT, typename SymbolT>
	class scoped_symboled_statement : public stmt::scoped_statement<ScopeT>, public stmt::symboled_statement<SymbolT>
	{
	public:
		scoped_symboled_statement()
		{
			//symboled_statement<SymbolT>::symbol.inner_scope = &(scoped_statement<ScopeType>::inner_scope);
		}
	};
}
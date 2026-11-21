
#pragma once

#include "stmt/statement.h"
#include "symbol/symbol.h"
#include "symbol_reference.h"
#include <type_traits>
#include "parser.h"
#include "symbol/function_symbol.h"
#include "core/castable_unique_ptr.h"

namespace stmt
{
	class symboled_statement_base : public virtual stmt::statement
	{
	public:
		virtual symbol* get_symbol() = 0;

		symbol_reference symbol_definition_reference;
	};

	template <typename T>
	concept symbol_type = std::is_base_of<symbol, T>::value;

	template <symbol_type SymbolT>
	class symboled_statement : public symboled_statement_base
	{
	public:
		virtual symbol* get_symbol() override { return symbol.get(); }

		void parse_symbol(parser& parser)
		{
			symbol_definition_reference = parser.read_symbol_reference();
			symbol = std::make_unique<SymbolT>(symbol_definition_reference);
			symbol_definition_reference.symbol = symbol;
		}

		castable_unique_ptr<SymbolT> symbol;
	};
}


#include "symbol_reference.h"

#include "compiler/symbol/symbol.h"
#include "token.h"
#include "compiler/stmt/statement.h"

symbol_reference::symbol_reference()
	: token{ nullptr }
	, symbol{ nullptr }
{
}

void symbol_reference::semantic_analyze(stmt::statement& statement)
{
	std::u16string token_text = token->get_source_text();
	symbol = statement.get_scope()->find_symbol(token_text, statement.sequence_number);

	if (symbol == nullptr)
	{
		auto message = u"unknown symbol '" + token_text + u"'";
		statement.diagnostics.push_back(lsp::diagnostic(token->range, lsp::diagnostic_severity::Error, 1, message));
	}
}
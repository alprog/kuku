
#pragma once

#include "compiler/token.h"
#include "compiler/parser.h"
#include "compiler/statement_scope.h"
#include "compiler/scope_type.h"
#include "lsp/diagnostic.h"

#define CHECK_END_OF_STATEMENT if (parser.current->is_end_statement_token()) return;

class compiler;

namespace stmt
{
	class statement
	{
	public:
		virtual ~statement();

		token* start_token;
		token* end_token;

		int sequence_number;

		bool is_valid;
		std::u16string error_text;

		statement* init(parser& parser, token* start_token);

		virtual scope_type get_allowed_scopes() const = 0;
		virtual std::u16string get_statement_type() const { return u"<unknown>"; }

		statement_scope* get_scope() const;
		std::u16string get_source_text() const;
		std::u16string get_hover_text() const;
		lsp::range get_full_range() const;
		void set_scope(statement_scope* scope);

		virtual void semantic_analyze();
		virtual void compile(compiler& compiler);
		virtual void define_symbols(statement_scope* scope);

		std::vector<lsp::diagnostic> diagnostics;

	protected:
		virtual void parse_internal(parser& parser) = 0;

		statement_scope* scope;
	};
}

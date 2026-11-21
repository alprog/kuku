
#include "statement.h"
#include "core/unexepected_error.h"

stmt::statement::~statement()
{
}

stmt::statement* stmt::statement::init(parser& parser, token* start_token)
{
	this->start_token = start_token;

	try
	{
		parse_internal(parser);
		this->end_token = parser.current;
		parser.require_end_of_statement();
		this->is_valid = true;
	}
	catch (unexpected_error)
	{
		this->is_valid = false;
		if (parser.current->type == token_type::end_of_line)
		{
			this->error_text = u"unexpected end of line";
		}
		else
		{
			this->error_text = u"unexpected token '" + parser.current->get_source_text() + u"'";
		}
		diagnostics.push_back(lsp::diagnostic(parser.current->range, lsp::diagnostic_severity::Error, 1, error_text) );

		while (!parser.current->is_end_statement_token()) parser.next(); // panic mode
		this->end_token = parser.current;
		parser.next();
	}

	return this;
}

statement_scope* stmt::statement::get_scope() const
{
	return scope;
}

std::u16string stmt::statement::get_source_text() const
{
	return start_token->document.get_substring(get_full_range());
}

std::u16string stmt::statement::get_hover_text() const
{
	const auto& text = 
		u"**statement:** "_s + get_statement_type() + u"  \r\n" +
		u"**content:** "_s + get_source_text();

	return text;
}

lsp::range stmt::statement::get_full_range() const
{
	return lsp::range(start_token->range.start, end_token->range.end);
}

void stmt::statement::set_scope(statement_scope* scope)
{
	this->scope = scope;
}

void stmt::statement::semantic_analyze()
{
}

void stmt::statement::compile(compiler& compiler)
{
}

void stmt::statement::define_symbols(statement_scope* scope)
{

}
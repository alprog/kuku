
#include "token.h"

token::token(token_type type, text_document& document, lsp::position start, lsp::position end)
    : type{ type }
    , document{ document }
    , range{ start, end }
{
}

token& token::operator=(token& token)
{
    type = token.type;
    document = token.document;
    range = token.range;
    return *this;
}

bool token::is_end_statement_token()
{
    return type == token_type::end_of_line || type == token_type::semicolon;
}

std::u16string token::get_hover_text()
{
    return u"**token:** "_s + get_u16name(type) + u"  \r\n" +
           u"**Content:** " + get_source_text();
}

std::u16string token::get_source_text()
{
    return document.get_substring(range);
}
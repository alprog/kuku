#pragma once

#include "token_type.h"
#include "lsp/range.h"
#include "text_document.h"
#include <string>
#include "symbol_reference.h"

namespace stmt
{
    class statement;
}

struct token
{
    token& operator=(token& token);
    token(token_type type, text_document& document, lsp::position start, lsp::position end);

    bool is_end_statement_token();

    std::u16string get_hover_text();
    std::u16string get_source_text();

    token_type type;
    text_document& document;
    lsp::range range;
    stmt::statement* statement;
};
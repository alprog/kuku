#pragma once

#include <string>
#include "token.h"
#include "token_type.h"
#include "core/types.h"
#include "text_document.h"
#include "source_iterator.h"

class lexer
{
public:
    lexer(text_document& text_document);
    token* get_next_token();

public:
    token* finish_line_comment(source_iterator start_it);
    token* finish_block_comment(source_iterator start_it);
    token* finish_binding_block_comment(source_iterator start_it);
    token* finish_string(source_iterator start_it, utf16unit end_quote, bool escaping);

    bool match(utf16unit symbol);

    bool move_after(utf16unit end_symbol);
    bool move_after_escaped(utf16unit end_symbol);

    token* create_token(source_iterator start, token_type type);

    text_document& text_document;
    source_iterator it;
};
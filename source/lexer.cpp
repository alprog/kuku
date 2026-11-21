
#include "lexer.h"

#include <map>
#include "core/console.h"

auto& get_keywords()
{
    static std::map<std::u16string, token_type> keywords {
        { u"and", token_type::keyword_and },
        { u"break", token_type::keyword_break },
        { u"class", token_type::keyword_class },
        { u"continue", token_type::keyword_continue },
        { u"do", token_type::keyword_do },
        { u"else", token_type::keyword_else },
        { u"end", token_type::keyword_end },
        { u"for", token_type::keyword_for },
        { u"function", token_type::keyword_function },
        { u"if", token_type::keyword_if },
        { u"in", token_type::keyword_in },
        { u"loop", token_type::keyword_loop },
        { u"or", token_type::keyword_or },
        { u"print", token_type::keyword_print },
        { u"return", token_type::keyword_return },
        { u"then", token_type::keyword_then },
        { u"var", token_type::keyword_var },
        { u"while", token_type::keyword_while }
    };

    return keywords;
}

lexer::lexer(::text_document& text_document)
    : text_document{ text_document }
    , it{ text_document }
{
}

bool is_digit(utf16unit c)
{
    return c >= '0' && c <= '9';
}

bool is_alpha(utf16unit c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool is_alpha_or_digit(wchar_t c)
{
    return is_digit(c) || is_alpha(c);
}

bool is_quote(utf16unit c)
{
    return c == '"' || c == '\'' || c == '`';
}

token* lexer::get_next_token()
{
    while (true)
    {
        utf16unit c = *it;
        switch (c)
        {
            case '\0':
                return create_token(it++, token_type::end_of_source);

            case '\n': 
                return create_token(it++, token_type::end_of_line);

            case ' ':
                ++it;
                continue;

            case '#':
            {
                auto startIt = it++;
                if (match('['))
                {
                    if (match('#'))
                        return create_token(startIt, token_type::comment); //:  #[#     disabled comment begin marker
                    else
                        return finish_block_comment(startIt);              //:  #[...   comment begin marker
                }
                else if (match(']'))
                    return create_token(startIt, token_type::comment);     //:  #]      comment end marker
                else
                    return finish_line_comment(startIt);                   //:  #...    single line comment
            }

            case '*':
            {
                auto startIt = it++;
                if (match('/'))
                    return finish_binding_block_comment(startIt);                 //:  */...    binding-comment begin marker
                else
                    return create_token(startIt, token_type::multiply_Operator);  //:  *        multiply operator
            }

            case '/':
            {
				auto startIt = it++;
				if (match('*'))
					return finish_line_comment(startIt);                        //:  /*...    single line binding-comment
				else
					return create_token(startIt, token_type::divide_Operator);  //:  /        divide operator
			}

            case '=':
            {
                auto startIt = it++;
                if (match('='))
                    return create_token(startIt, token_type::equal_operator);   //: ==
                else
                    return create_token(startIt, token_type::assign_operator);  //: =
            }

            case '<':
            {
                auto startIt = it++;
                if (match('='))
                    return create_token(startIt, token_type::less_or_equal_operator);  //: <=
                else
                    return create_token(startIt, token_type::less_operator);           //: <
            }

            case '>':
            {
                auto startIt = it++;
                if (match('='))
                    return create_token(startIt, token_type::greater_or_equal_operator);  //: >=
                else
                    return create_token(startIt, token_type::greater_operator);           //: >
            }

            case '!':
            {
                auto startIt = it++;
                if (match('='))
                    return create_token(startIt, token_type::not_equal_operator); //: !=
                else
                    return create_token(startIt, token_type::not_operator);       //: !
            }

            case '.':
            {
                auto startIt = it++;
                if (match('.'))
                    return create_token(startIt, token_type::double_dot); //: ..
                else
                    return create_token(startIt, token_type::dot);       //: .
            }

            case '^': return create_token(it++, token_type::exponent_operator);
            case '-': return create_token(it++, token_type::minus_operator);
            case '+': return create_token(it++, token_type::plus_operator);            
            case ':': return create_token(it++, token_type::colon);
            case ';': return create_token(it++, token_type::semicolon);
            case ',': return create_token(it++, token_type::comma);
            case '[': return create_token(it++, token_type::open_bracket);
            case ']': return create_token(it++, token_type::close_bracket);
            case '{': return create_token(it++, token_type::open_brace);
            case '}': return create_token(it++, token_type::close_brace);
            case '(': return create_token(it++, token_type::open_parenthesis);
            case ')': return create_token(it++, token_type::close_parenthesis);
		}

		if (is_quote(c))
		{
            auto start_i = it++;
            return finish_string(start_i, c, true);
        }

        if (is_digit(c) || c == '-')
        {
            auto startIt = it++;
            while (is_digit(*it)) ++it;
            auto it2 = it;
            if (*it2++ == '.' && *it2 != '.')
            {
                ++it;
                while (is_digit(*it)) ++it;
                return create_token(startIt, token_type::number_literal);
            }
            return create_token(startIt, token_type::integer_literal);
        }

        if (is_alpha(c))
        {
            auto startIt = it++;
            while (is_alpha_or_digit(*it)) ++it;

            std::u16string id = text_document.get_substring({ startIt.position, it.position });
            if (id == u"R" && is_quote(*it))
            {
                return finish_string(startIt, *it++, false);
            }
            if (id == u"true" || id == u"false")
            {
                return create_token(startIt, token_type::bool_literal);
            }

            auto it = get_keywords().find(id);
            if (it != std::end(get_keywords()))
            {
                return create_token(startIt, it->second);
            }

            return create_token(startIt, token_type::identifier);
        }

        ++it;
    }
}

token* lexer::finish_line_comment(source_iterator start_it)
{
    while (*it != '\n') ++it;
    return create_token(start_it, token_type::comment);
}

token* lexer::finish_block_comment(source_iterator start_it)
{
    int level = 1;

    while (move_after('#'))
    {
        if (match('['))
        {
            level++;
        }
        else if (match(']'))
        {
            if (--level == 0)
                break;
        }
    }

    return create_token(start_it, token_type::comment);
}

token* lexer::finish_binding_block_comment(source_iterator start_it)
{
    while (move_after('/'))
    {
        if (match('*'))
            break;
    }
    return create_token(start_it, token_type::comment);
}

token* lexer::finish_string(source_iterator start_it, utf16unit end_quote, bool escaping)
{
    auto result = escaping ? move_after_escaped(end_quote) : move_after(end_quote);
    if (result)
    {
        return create_token(start_it, token_type::string_literal);
    }
    else
    {
        return create_token(start_it, token_type::unclosed_string_literal);
    }
}

// check current symbol and step forward if it match
bool lexer::match(utf16unit symbol)
{
    if (*it == symbol)
    {
        ++it;
        return true;
    }
    return false;
}

bool lexer::move_after(utf16unit end_symbol)
{
    utf16unit cur = *it;
    while (cur != '\0')
    {
        it++;
        if (cur == end_symbol)
        {            
            return true;
        }
        cur = *it;
    }
    return false;
}

bool lexer::move_after_escaped(utf16unit end_symbol)
{
    utf16unit cur = *it;
    bool escaping = false;
    while (cur != '\0' && cur != '\n')
    {        
        it++;
        if (escaping)
        {
            escaping = false;
        }
        else if (cur == '\\')
        {
            escaping = true;
        }
        else if (cur == end_symbol)
        {            
            return true;
        }
        cur = *it;
    }
    return false;
}

token* lexer::create_token(source_iterator start_it, token_type type)
{
    return new token { type, text_document, start_it.position, it.position };
}

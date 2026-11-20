
#include "source_iterator.h"
#include "unicode/unicode.h"
#include "text_document.h"

source_iterator::source_iterator(::text_document& text_document)
    : text_document{ text_document }
    , position{ 0, 0 }
{
}

utf16unit source_iterator::operator*()
{
    return text_document.get_character(position);
}

// pre-increment
source_iterator& source_iterator::operator++()
{
    position.character++;

    if (position.line < text_document.lines.size())
    {
        auto& line = text_document.lines[position.line];
        if (position.character > line.size())
        {
            position.line++;
            position.character = 0;
        }
    }

    return *this;
}

// post-increment
source_iterator source_iterator::operator++(int)
{
    auto old = *this;
    operator++();
    return old;
}

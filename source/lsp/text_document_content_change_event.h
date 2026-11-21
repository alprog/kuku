
#pragma once

#include <string>
#include "lsp/range.h"
#include "core/json/serializable.h"
#include "core/json/scheme.h"

namespace lsp
{
    struct text_document_content_change_event : public json::serializable
    {
        range range;
        std::u16string text;

        JSCHEME(range, text)
    };
}
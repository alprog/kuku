
#pragma once

#include <string>
#include "core/json/serializable.h"
#include "core/json/field.h"
#include "core/json/scheme.h"

#include <type_traits>

namespace lsp
{
    struct position : public json::serializable
    {
        position(int line = 0, int character = 0);

        int line;
        int character;

        std::u16string to_str();

        std::strong_ordering operator<=>(const position& other) const;

        JSCHEME(line, character)
    };
}
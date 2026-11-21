
#pragma once

#include "core/json/serializable.h"
#include "lsp/position.h"

namespace lsp
{
    struct range : public json::serializable
    {
        range(position start = {}, position end = {});

        bool contains(position position);

        position start;
        position end;

        JSCHEME(start, end)
    };
}
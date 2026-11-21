
#pragma once

#include <string>
#include "core/json/serializable.h"
#include "core/json/scheme.h"

namespace lsp
{
    struct text_document_identifier : public json::serializable
    {
        std::string uri;

        JSCHEME(JFIELD(uri))
    };
}
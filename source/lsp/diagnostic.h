
#pragma once

#include <string>
#include "core/json/serializable.h"
#include "core/json/field.h"
#include "core/json/scheme.h"
#include "enums.h"
#include "range.h"

namespace lsp
{
    struct diagnostic : public json::serializable
    {
        diagnostic(lsp::range range, diagnostic_severity severity, int code, std::u16string message);

        lsp::range range;
        diagnostic_severity severity;
        int code;
        std::u16string message;
        
        JSCHEME(range, severity, code, message)
    };
}
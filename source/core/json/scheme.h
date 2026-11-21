#pragma once

#include <vector>
#include "core/json/field.h"

namespace json
{
    class scheme
    {
    public:
        scheme(std::vector<json::base_field*> fields)
            : fields{ fields }
        {
        }

        std::vector<json::base_field*> fields;
    };
}

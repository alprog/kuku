#pragma once

#include <string>
#include "data_type.h"

namespace rt
{
    class user_class;
    class function;

    enum class property_mode
    {
        direct,
        virtualized,
        getter
    };

    class property
    {
    public:
        std::string name;

        property_mode mode;
        user_class* type;

        int offset; // direct mode
        function* function; // getter

        user_class& owner_class;
    };
}
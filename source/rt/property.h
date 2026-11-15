#pragma once

#include <string>
#include "data_type.h"

namespace rt
{
    class user_class;

    class property
    {
    public:
        property(user_class& owner_class, std::string name, data_type type, int instance_offset);

        user_class& owner_class;
        data_type type;
        std::string name;
        int instance_offset;
    };
}
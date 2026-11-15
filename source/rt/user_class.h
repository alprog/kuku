#pragma once

#include <string>
#include <vector>
#include "function.h"
#include "data_type.h"
#include "property.h"
#include "instance.h"

namespace rt
{
    class user_class
    {
    public:
        user_class(std::string name);

        std::string name;

        property& register_field(std::string name, data_type data_type);
        instance create_instance();

        void dump(instance instance);

        int instance_size;

        std::vector<property> properties;
    };
}
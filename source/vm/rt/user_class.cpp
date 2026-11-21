#include "user_class.h"
#include <iostream>
#include "vm/cell.h"

rt::user_class::user_class(std::string name)
    : name{name}
    , instance_size{1}
{
}

//rt::property& rt::user_class::register_field(std::string name, data_type data_type)
//{
//    return properties.emplace_back(*this, name, data_type, instance_size++);
//}

instance rt::user_class::create_instance()
{
    instance instance;
    instance.cells = new cell[instance_size];
    instance.cells[0].class_pointer = this;
    return instance;
}

void rt::user_class::dump(instance instance)
{
    std::cout << sizeof(instance) << std::endl;

    std::cout << instance.cells[0].class_pointer->name << std::endl;
    for (auto& property : properties)
    {
        auto value = instance.cells[property->offset].number;
        std::cout << property->name << " " << value << std::endl;
    }
}
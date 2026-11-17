#include "type_registry.h"

type_registry::type_registry()
{
    classes.reserve(100); // TODO: make stable vectors
    properties.reserve(100);
    functions.reserve(100);
}

rt::user_class& type_registry::get_class(std::string name)
{
    uint64_t hash = symbol_table.getHash(name);
    uint16_t index = symbol_table.getValue(hash);
    if (index == -1)
    {
        index = classes.size();
        symbol_table.setValue(hash, index);
        classes.emplace_back(name);
    }
    return classes[index];
}
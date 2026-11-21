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
    if (index == symbol_table::invalid_index)
    {
        index = classes.size();
        symbol_table.setValue(hash, index);
        classes.emplace_back(name);
    }
    return classes[index];
}

rt::property& type_registry::get_property(rt::user_class& owner, const std::string& identity, std::string type)
{
    auto& property_type = get_class(type);

    uint64_t hash = symbol_table.getHash(identity);
    uint16_t index = symbol_table.getValue(hash);
    if (index == symbol_table::invalid_index)
    {
        index = properties.size();
        symbol_table.setValue(hash, index);
        properties.push_back({ identity, rt::property_mode::direct, &property_type, 0, nullptr, owner });
        owner.properties.push_back(&properties[index]);
    }
    else if (properties[index].type != &property_type)
    {
        throw std::exception("property type conflict");
    }
    return properties[index];
}

rt::function& type_registry::get_function(rt::user_class& owner, const std::string& identity, std::vector<std::string> params, std::string result)
{
    for (auto& param : params)
    {
        get_class(param);
    }

    if (!result.empty())
    {
        get_class(result);
    }

    uint64_t hash = symbol_table.getHash(identity);
    uint16_t index = symbol_table.getValue(hash);
    if (index == symbol_table::invalid_index)
    {
        index = functions.size();
        symbol_table.setValue(hash, index);
        auto& function = functions.emplace_back();
        function.name = identity;
    }
    return functions[index];
}
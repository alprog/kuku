
#pragma once

#include "json.h"

#include "unicode/unicode_streams.h"

namespace nlohmann
{
    template <>
    struct adl_serializer<std::u8string>
    {
        static_assert(sizeof(std::u8string::value_type) == sizeof(std::string::value_type));

        static void to_json(json& j, const std::u8string& value)
        { 
            nlohmann::to_json(j, reinterpret_cast<const std::string&>(value));
        }

        static void from_json(const json& j, std::u8string& value)
        {
            nlohmann::from_json(j, reinterpret_cast<std::string&>(value));
        }
    };

    template <>
    struct adl_serializer<std::u16string>
    {
        static void to_json(json& j, const std::u16string& u16string)
        {
            auto utf8string = unicode::to_utf8(u16string);
            nlohmann::to_json(j, utf8string);
        }

        static void from_json(const json& j, std::u16string& u16string)
        {
            std::u8string u8string;
            nlohmann::from_json(j, reinterpret_cast<std::string&>(u8string));
            u16string = unicode::to_utf16(u8string);
        }
    };
}

#pragma once

#include <vector>
#include <string>
#include "utils.h"

template <typename T>
struct enum_reflector
{
};

#define reflectable_enum_internal(EnumName, type, ...) \
	enum class EnumName : type { __VA_ARGS__ }; \
	template <> \
	struct enum_reflector<EnumName> \
	{ \
		static std::string get_enum_name(EnumName value) \
		{ \
			static auto vector = split<std::string>(#__VA_ARGS__, ", "); \
			return vector[(int)value]; \
		}; \
	};

#define reflectable_enum(...) reflectable_enum_internal(__VA_ARGS__)

template <typename EnumT>
std::string get_name(EnumT value)
{
	return enum_reflector<EnumT>::get_enum_name(value);
};

template <typename EnumT>
std::u16string get_u16name(EnumT value)
{
	auto name = enum_reflector<EnumT>::get_enum_name(value);
	return std::u16string(std::begin(name), std::end(name));
};
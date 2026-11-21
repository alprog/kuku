
#include "guid.h"
#include "base64.h"

guid::guid()
	: value{ 0 }
{
}

guid::guid(uint64_t value)
	: value{ value }
{
}

guid::guid(std::string string)
{
	base64::convert_4_characters_to_3_bytes(&string[0], &bytes[0]);
	base64::convert_4_characters_to_3_bytes(&string[4], &bytes[3]);
}

std::string guid::to_string()
{
	std::string string;
	string.resize(8);
	base64::convert_3_bytes_to_4_characters(&bytes[0], &string[0]);
	base64::convert_3_bytes_to_4_characters(&bytes[3], &string[4]);
	return string;
}

template <>
struct std::hash<guid>
{
    std::size_t operator()(const guid& g) const
    {
		return g.value;
    }
};
#pragma once

#include "types.h"
#include <vector>
#include <cstring>

class bytecode
{
public:
	std::vector<byte> bytes;

	byte* get_start_pointer();
	byte* get_end_pointer();

	template<typename T>
	void write(const T& value)
	{
		size_t end = bytes.size();
		bytes.resize(end + sizeof(T));
		memcpy(&bytes[end], &value, sizeof(T));
	}
};

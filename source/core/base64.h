
#pragma once

#include "types.h"
#include <string>
#include <sstream>
#include <vector>

namespace base64
{
	void convert_4_characters_to_3_bytes(char* characters, byte* bytes);
	void convert_3_bytes_to_4_characters(byte* bytes, char* characters);
}
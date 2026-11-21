
#pragma once

#include "types.h"

// 48bit-guid

// collision probabilities:

//  N     Collision chance
// 100K        0.002%
// 500K        0.05%
//   1M        0.2%
//   2M        0.7%
//   3M        1.5%
//  10M        16%
//  20M        50%

struct guid
{
	guid();
	guid(uint64_t value);
	guid(std::string string);

	union
	{
		uint64_t value : 48;
		byte bytes[6];
	};

	std::string to_string();
};

template <>
struct std::hash<guid>;
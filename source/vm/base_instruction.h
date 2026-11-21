#pragma once

#include "opcode.h"

#pragma pack(push, 1)

struct base_instruction
{
	opcode opcode;
};

#pragma pack(pop)

static_assert(sizeof(base_instruction) == 1);

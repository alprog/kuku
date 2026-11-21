
#pragma once

#include "token_type.h"
#include "precedence.h"
#include <vector>

struct binary_operator
{
	token_type token_type;
	precedence precedence;
};

std::vector<binary_operator>& get_binary_operators();

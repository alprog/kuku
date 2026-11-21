
#pragma once

enum class precedence
{
	exponentiation = 1,
	multiplication = 2,
	addition = 3,
	relational = 4,
	equality = 5,
	logic = 6,
	maximum = 7
};
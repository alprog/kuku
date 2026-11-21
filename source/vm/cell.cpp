#include "cell.h"

cell::cell(int integer)
	: integer { integer }
{
}

std::strong_ordering cell::operator<=>(const cell& other) const
{
	if (integer == other.integer)
	{
		return std::strong_ordering::equal;
	}
	else if (integer < other.integer)
	{
		return std::strong_ordering::less;
	}
	else
	{
		return std::strong_ordering::greater;
	}
}

bool cell::operator==(const cell& other) const
{
	return integer == other.integer;
}

bool cell::operator!=(const cell& other) const
{
	return integer != other.integer;
}
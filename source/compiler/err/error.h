
#pragma once

#include <string>

class error
{
public:
	virtual std::u16string get_message() = 0;
};
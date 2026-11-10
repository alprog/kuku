#pragma once

#include <string>
#include "rt/function.h"

class decompiler
{
public:
	void print_instructions(rt::function& function, bool include_comments);

private:
	std::string get_comment(rt::function& function, int index, base_instruction& instruction);
	std::string pop_comment();
	std::string push_comment();

	bool replace(std::string& str, std::string substr, std::string newstr);
	bool replace(std::string& str, std::string substr, std::string (decompiler::*callback)());

	int stack_size = 0;
};

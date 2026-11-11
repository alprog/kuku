#pragma once

#include <string>
#include <vector>
#include "rt/function.h"

class decompiler
{
public:
	void print_instructions(rt::function& function, bool include_comments);

private:
	std::string get_comment(rt::function& function, int offset, byte* ptr);
	std::string pop_comment();
	std::string push_comment();
	void save_stack_comment(std::string comment);

	bool replace(std::string& str, std::string substr, std::string newstr);
	bool replace(std::string& str, std::string substr, std::string (decompiler::*callback)());

	std::vector<std::string> stack_comments;
};

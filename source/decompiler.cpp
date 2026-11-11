#include "decompiler.h"

#include "console.h"
#include <format>
#include "jump_table.h"
#include "instructions.h"
#include <functional>

bool full_mode = true;

void decompiler::print_instructions(rt::function& function, bool include_comments)
{
	stack_comments.clear();

	byte* start = function.bytecode.get_start_pointer();
	byte* end = function.bytecode.get_end_pointer();

	for (byte* ptr = start; ptr < end; ptr += jump_table::get_size_function[*ptr]())
	{
		int offset = (int)(ptr - start);
		auto info = jump_table::get_info_function[*ptr]();

		auto comment = get_comment(function, offset, ptr);

		auto line = std::format("{:3} | {:22} | ", offset, info->to_string(ptr));

		if (include_comments)
		{
			line += comment;
		}

		console::write_line(line);
	}
}

static bool perform_replacement(std::string& comment, const instruction_info& info, byte* ptr, std::string macro_name, std::function<std::string(int)> macro)
{
	auto macro_start = comment.find(macro_name + "(");
	if (macro_start != std::string::npos)
	{
		auto macro_end = comment.find(")", macro_start) + 1;
		auto arg_start = macro_start + macro_name.size() + 1;
		auto arg_name = comment.substr(arg_start, macro_end - arg_start - 1);
		auto arg_value = info.get_argument_value(ptr, arg_name);
		comment.replace(macro_start, macro_end - macro_start, macro(arg_value));
		return true;
	}
	return false;
}

bool decompiler::replace(std::string& str, std::string substr, std::string newstr)
{
	auto start = str.find(substr);
	if (start != std::string::npos)
	{
		str.replace(start, substr.size(), newstr);
		return true;
	}
	return false;
}

bool decompiler::replace(std::string& str, std::string substr, std::string (decompiler::*callback)())
{
	auto start = str.rfind(substr);
	if (start != std::string::npos)
	{
		str.replace(start, substr.size(), (this->*callback)());
		return true;
	}
	return false;
}

std::string decompiler::get_comment(rt::function& function, int offset, byte* ptr)
{
	auto& info = *jump_table::get_info_function[*ptr]();
	int size = (int)jump_table::get_size_function[*ptr]();
	std::string comment = info.comment;

	auto R = [&](int value)
	{
		auto name = function.get_local_info(offset, value).name;
		return std::string(std::begin(name), std::end(name));
	};

	auto K = [&](int value) { return std::to_string(function.constant_buffer[value].integer); };

	auto INT = [&](int value) { return std::to_string(value); };

	auto JMP = [&](int value) { return std::to_string(offset + size + value); };

	while (replace(comment, "POP", &decompiler::pop_comment)) {}

	while (perform_replacement(comment, info, ptr, "R", R)) {}
	while (perform_replacement(comment, info, ptr, "K", K)) {}
	while (perform_replacement(comment, info, ptr, "INT", INT)) {}
	while (perform_replacement(comment, info, ptr, "JMP", JMP)) {}

	const std::string prefix = "PUSH = ";
	if (comment.starts_with(prefix))
	{
		stack_comments.push_back(comment.substr(prefix.size()));
	}

	replace(comment, "PUSH", &decompiler::push_comment);

	if (full_mode && comment.starts_with("%"))
	{
		comment = "";
	}

	return comment;
}

std::string decompiler::pop_comment()
{
	auto comment = stack_comments[stack_comments.size() - 1];
	stack_comments.pop_back();
	if (full_mode)
	{
		return comment;
	}
	else
	{
		return "%" + std::to_string(stack_comments.size());
	}
}

std::string decompiler::push_comment()
{
	return "%" + std::to_string(stack_comments.size());
}

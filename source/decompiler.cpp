#include "decompiler.h"

#include "console.h"
#include <format>
#include "jump_table.h"
#include "instructions.h"
#include <functional>

void decompiler::print_instructions(rt::function& function, bool include_comments)
{
	stack_size = 0;

	int index = 0;
	for (auto& instruction : function.bytecode.instructions)
	{
		auto info = jump_table::get_info_function[instruction.I]();


		auto comment = get_comment(function, index, instruction);

		auto line = std::format("{:3} | {:22} | ", index++, info->to_string(instruction));

		if (include_comments)
		{
			line += comment;
		}

		console::write_line(line);
	}
}

static bool perform_replacement(std::string& comment, base_instruction& instruction, std::string macro_name, std::function<std::string(int)> macro)
{
	auto macro_start = comment.find(macro_name + "(");
	if (macro_start != std::string::npos)
	{
		auto macro_end = comment.find(")", macro_start) + 1;
		auto arg_start = macro_start + macro_name.size() + 1;
		auto arg_name = comment.substr(arg_start, macro_end - arg_start - 1);
		auto arg_value = instruction.get_argument_value(arg_name);
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

std::string decompiler::get_comment(rt::function& function, int index, base_instruction& instruction)
{
	auto info = jump_table::get_info_function[instruction.I]();
	std::string comment = info->comment;
	if (info->has_arg(instruction_args::MB) && instruction.MB == instruction_mode::K)
	{
		replace(comment, "R(B)", "K(B)");
	}
	if (info->has_arg(instruction_args::MC) && instruction.MC == instruction_mode::K)
	{
		replace(comment, "R(C)", "K(C)");
	}

	auto R = [&](int value)
	{
		auto name = function.get_local_info(index, value).name;
		return std::string(std::begin(name), end(name));
	};

	auto K = [&](int value) { return std::to_string(function.constant_buffer[value].integer); };

	auto INT = [&](int value) { return std::to_string(value); };

	auto JMP = [&](int value) { return std::to_string(index + value); };

	while (replace(comment, "POP", &decompiler::pop_comment)) {}

	while (perform_replacement(comment, instruction, "R", R)) {}
	while (perform_replacement(comment, instruction, "K", K)) {}
	while (perform_replacement(comment, instruction, "INT", INT)) {}
	while (perform_replacement(comment, instruction, "JMP", JMP)) {}

	replace(comment, "PUSH", &decompiler::push_comment);

	return comment;
}

std::string decompiler::pop_comment()
{
	return "%" + std::to_string(--stack_size);
}

std::string decompiler::push_comment()
{
	return "%" + std::to_string(stack_size++);
}

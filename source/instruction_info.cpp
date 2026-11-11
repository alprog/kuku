
#include "instruction_info.h"
#include "opcode.h"
#include <sstream>
#include <iomanip>

int instruction_info::get_argument_value(byte* ptr, const std::string& name) const
{
	ptr += sizeof(opcode);
	for (auto& arg : arguments)
	{
		if (arg.name == name)
		{
			return arg.meta->get_value(ptr);
		}
		ptr += arg.meta->get_size();
	}

	throw std::exception("trying to get not valid argument");
}

std::string instruction_info::to_string(byte* ptr) const
{
	std::stringstream ss;

	ss << std::left << std::setw(10) << get_name(*reinterpret_cast<opcode*>(ptr));

	ptr += sizeof(opcode);
	for (auto& arg : arguments)
	{
		ss << std::left << std::setw(4) << arg.meta->to_string(ptr);
		ptr += arg.meta->get_size();
	}

	return ss.str();
}

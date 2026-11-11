
#include "instruction_info.h"
#include "opcode.h"
#include <sstream>
#include <iomanip>

std::string instruction_info::to_string(byte* ptr) const
{
	std::stringstream ss;

	ss << std::left << std::setw(10) << get_name(*reinterpret_cast<opcode*>(ptr));

	ptr += sizeof(opcode);
	for (auto& arg : arguments)
	{
		ss << std::left << std::setw(4) << arg->to_string(ptr);
		ptr += arg->get_size();
	}

	return ss.str();
}

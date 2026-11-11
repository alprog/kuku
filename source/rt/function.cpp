#include "function.h"
//#include "decompiler.h"

#include "console.h"
#include "unicode.h"
#include <format>
#include "jump_table.h"
#include "unicode.h"
#include "instructions.h"
#include <functional>

const rt::localvar_info& rt::function::get_local_info(int instruction_offset, int stack_offset) const
{
	for (const auto& info : locals)
	{
		if (info.stack_offset == stack_offset)
		{
			if (instruction_offset >= info.start_instruction && instruction_offset <= info.end_instruction)
			{
				return info;
			}
		}
	}

	static std::vector<localvar_info> temporaries;
	if (temporaries.size() == 0)
	{
		for (int i = 0; i < 100; i++)
		{
			auto name = "%" + std::to_string(i);
			temporaries.push_back( { std::u16string(std::begin(name), std::end(name)) } );
		}
	}

	return temporaries[stack_offset];
}

byte rt::function::add_constant(cell cell)
{
	for (int i = 0; i < constant_buffer.size(); i++)
	{
		if (cell == constant_buffer[i])
		{
			return i;
		}
	}
	constant_buffer.push_back(cell);
	return constant_buffer.size() - 1;
}

void rt::function::full_dump()
{
	console::write_line(name);
	//decompiler().print_instructions(*this, true);
	console::new_line();
	print_constant_buffer();
	console::new_line();
	print_locals_info();
}

void rt::function::print_constant_buffer()
{
	for (int i = 0; i < constant_buffer.size(); i++)
	{
		console::write_line(std::format("{:<3} {:<3} {}", i, i + 128, constant_buffer[i].integer));
	}
}

void rt::function::print_locals_info()
{
	console::write_line("TYPE OFFSET START END NAME");

	for (auto& info : locals)
	{
		auto record = std::format("{:<4} {:<6} {:<5} {:<4}", (int)info.type_index, info.stack_offset, info.start_instruction, info.end_instruction);
		console::write(record);
		console::write_line(info.name);
	}
}

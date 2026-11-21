
#include "jump_table.h"
#include "instructions.h"

execute_function_ptr jump_table::execute_function[INSTRUCTION_COUNT];
get_size_function_ptr jump_table::get_size_function[INSTRUCTION_COUNT];
get_info_function_ptr jump_table::get_info_function[INSTRUCTION_COUNT];

//------------------------------------------------------------------------------

template <typename T>
inline void execute_instruction(routine& routine)
{
	auto instruction = reinterpret_cast<T*>(routine.call_frame.ip);
	routine.call_frame.ip += sizeof(T);
	instruction->execute(routine);
}

template <typename T>
inline size_t get_size()
{
	return sizeof(T);
}

template <typename T>
inline instruction_info* get_info()
{
	static instruction_info info = T::create_info();
	return &info;
}

template <int I>
void register_instruction()
{
	using instructionT = instruction<(opcode)I>;
	jump_table::execute_function[I] = execute_instruction<instructionT>;
	jump_table::get_size_function[I] = get_size<instructionT>;
	jump_table::get_info_function[I] = get_info<instructionT>;
};

template <int I>
void register_instruction_recursive()
{
	register_instruction<I>();
	register_instruction_recursive<I - 1>();
}

template <>
void register_instruction_recursive<0>()
{
	register_instruction<0>();
}

void jump_table::init()
{
	register_instruction_recursive<255>();
}

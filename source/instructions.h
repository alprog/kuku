#pragma once

#include "base_instruction.h"
#include "routine.h"
#include <iostream>
#include "instruction_info.h"
#include "virtual_machine.h"
#include "instruction_args.h"
#include "preprocessor/for_each.h"
#include "protected_instruction.h"
#include "instruction_info.h"

#pragma warning( disable : 4003 )

#define MACRO_ARG_A (uint8_t, A)
#define MACRO_ARG_B (uint8_t, B)
#define MACRO_ARG_C (uint8_t, C)
#define MACRO_ARG_Bx (uint16_t, Bx)
#define MACRO_ARG_sBx (int16_t, sBx)
#define MACRO_ARG_MB (instruction_mode, MB)
#define MACRO_ARG_M2 (instruction_mode, M2)

#define MACRO_ARGS_NONE
#define MACRO_ARGS_A     MACRO_ARG_A
#define MACRO_ARGS_AB    MACRO_ARG_A, MACRO_ARG_B
#define MACRO_ARGS_MAB   MACRO_ARG_MB, MACRO_ARG_A, MACRO_ARG_B
#define MACRO_ARGS_ABx   MACRO_ARG_A, MACRO_ARG_Bx
#define MACRO_ARGS_sBx   MACRO_ARG_sBx
#define MACRO_ARGS_AsBx  MACRO_ARG_A, MACRO_ARG_sBx
#define MACRO_ARGS_ABC   MACRO_ARG_A, MACRO_ARG_B, MACRO_ARG_C

#define MACRO_ARGS_M2ABC MACRO_ARG_M2, MACRO_ARG_A, MACRO_ARG_B, MACRO_ARG_C

#define FIRST(first, second) first
#define SECOND(first, second) second
#define BOTH(x) FIRST x SECOND x
#define USING(x) using base_instruction::SECOND x;
#define INITIALIZATION(x) this->SECOND x = SECOND x;
#define ARGUMENT(x) | CONCATENATE(instruction_args::, SECOND x)

template <opcode, instruction_mode MODE = instruction_mode::RR>
struct instruction : private protected_instruction
{
	inline void execute(routine& routine)
	{
		throw std::exception("not implemented");
	}

	static instruction_info create_info()
	{
		return { opcode::END, "unknown", "", instruction_args::NONE};
	}

	static const instruction_args args = instruction_args::invalid;

	inline static instruction_info info = { opcode::END, "", args };
};

#define Ins_X(NAME, COMMENT, ...) \
using instruction_##NAME = instruction<opcode::NAME>; \
template<instruction_mode MODE> \
struct instruction<opcode::NAME, MODE> : public protected_instruction \
{ \
	using base_instruction::opcode; \
	FOR_EACH(USING, __VA_ARGS__) \
	instruction( FOR_EACH_WITH_COMMA(BOTH, __VA_ARGS__) ) \
	{ \
		opcode = opcode::NAME; \
		FOR_EACH(INITIALIZATION, __VA_ARGS__) \
	} \
	instruction(instruction<opcode::NAME>&&) = delete; \
	static const instruction_args args = instruction_args::NONE FOR_EACH(ARGUMENT, __VA_ARGS__); \
	static instruction_info create_info() { return { opcode::NAME, COMMENT, args }; } \
	inline void execute(routine& routine)

#define Ins(NAME, COMMENT, ARGUMENTS) Ins_X(NAME, COMMENT, EXPAND(CONCATENATE(MACRO_ARGS_, ARGUMENTS)))

//--------------------------------------------------------------------------------------------

#define cellB static_cast<cell&>( routine.call_frame.get_cell<MODE & 1>(B) )
#define cellC static_cast<cell&>( routine.call_frame.get_cell<(MODE >> 1 & 1)>(C) )

Ins(VALUE, "R(A) = INT(sBx)", AsBx)
{
	routine.call_frame.stack[A].integer = sBx;
}};

Ins(LOADVAR, "R(A)", A)
{
	routine.push(routine.call_frame.stack[A]);
}};

Ins(SAVEVAR, "R(A) =", A)
{
	routine.call_frame.stack[A] = routine.pop();
}};

//------------

Ins(ADD, "A + B", NONE)
{
	routine.top[-2].integer = routine.top[-2].integer + routine.top[-1].integer;
	routine.top--;
}};

Ins(SUB, "A - B", NONE)
{
	routine.top[-2].integer = routine.top[-2].integer - routine.top[-1].integer;
	routine.top--;
}};

Ins(MULT, "A * B", NONE)
{
	routine.top[-2].integer = routine.top[-2].integer * routine.top[-1].integer;
	routine.top--;
}};

Ins(DIVIDE, "A / B", NONE)
{
	routine.top[-2].integer = routine.top[-2].integer / routine.top[-1].integer;
	routine.top--;
}};

Ins(POWER, "A ^ B", NONE)
{
	routine.top[-2].integer = std::pow(routine.top[-2].integer, routine.top[-1].integer);
	routine.top--;
}};

Ins(EQ, "A == B", NONE)
{
	routine.top[-2].boolean = routine.top[-2].integer == routine.top[-1].integer;
	routine.top--;
}};

Ins(NEQ, "A != B", NONE)
{
	routine.top[-2].boolean = routine.top[-2].integer != routine.top[-1].integer;
	routine.top--;
}};

Ins(L, "A < B", NONE)
{
	routine.top[-2].boolean = routine.top[-2].integer < routine.top[-1].integer;
	routine.top--;
}};

Ins(G, "A > B", NONE)
{
	routine.top[-2].boolean = routine.top[-2].integer > routine.top[-1].integer;
	routine.top--;
}};

Ins(LEQ, "A <= B", NONE)
{
	routine.top[-2].boolean = routine.top[-2].integer <= routine.top[-1].integer;
	routine.top--;
}};

Ins(GEQ, "A >= B", NONE)
{
	routine.top[-2].boolean = routine.top[-2].integer >= routine.top[-1].integer;
	routine.top--;
}};

//--------------

Ins(PUSH_K, "K(A)", A)
{
	routine.push(routine.call_frame.function->constant_buffer[A]);
}};

Ins(JUMP, "goto JMP(sBx)", sBx)
{
	routine.call_frame.ip += sBx;
}};

Ins(IFJUMP, "if !TOP then goto JMP(sBx)", sBx)
{
	routine.call_frame.ip += routine.pop().boolean ? 1 : sBx;
}};

Ins(PRINT, "print TOP", NONE)
{
	std::cout << routine.pop().integer << std::endl;
}};

Ins(CREATE_OBJECT, "R(A) = new CLS(Bx)", ABx)
{
	routine.call_frame.stack[A].object_index = routine.vm.object_storage.create_object(Bx);
}};

Ins(SET_FIELD, "R(A).FLD(B) = R(C)", ABC)
{
	object_index object_index = routine.call_frame.stack[A].object_index;
	routine.vm.object_storage.get_object(object_index).data[B] = routine.call_frame.stack[C];
}};

Ins(VIRTUAL_CALL, "call FNC(B) with INT(A) args", AB)
{
	cell* frame_start = &routine.call_frame.stack[-A];
	object_header& self = routine.vm.object_storage.get_object(frame_start->object_index);
	rt::user_class& self_class = routine.vm.type_registry.classes[self.class_index];
	rt::function& function = self_class.vtable[B];
	routine.push_call_frame(function, frame_start);
}};

Ins(INC, "R(A) += 1", A)
{
	routine.call_frame.stack[A].integer++;
}};

Ins(END, "end", NONE)
{
	routine.stop();
}};

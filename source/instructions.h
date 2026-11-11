#pragma once

#include "base_instruction.h"
#include "routine.h"
#include <iostream>
#include "instruction_info.h"
#include "virtual_machine.h"
#include "preprocessor/for_each.h"

template <opcode Code>
struct instruction : base_instruction
{
	instruction() : base_instruction{ Code } {};

	static instruction_info create_info() { return { Code, "unknown" }; }

	inline void execute(routine& routine)
	{
		throw std::exception("not implemented");
	}
};

#define FIRST(first, second) first
#define SECOND(first, second) second
#define BOTH(x) FIRST x SECOND x
#define DECLARATION(x) FIRST x SECOND x;
#define INITIALIZATION(x) , SECOND x { SECOND x }
#define ARGUMENT_X(type, name) instruction_arg{ #name, instruction_arg_meta<type>::get_instance() }
#define ARGUMENT_META(x) ARGUMENT_X x

#define Ins(NAME, COMMENT, ...) \
	using instruction_##NAME = instruction<opcode::NAME>; \
	template<> \
	struct instruction<opcode::NAME> : base_instruction \
	{ \
		FOR_EACH(DECLARATION, __VA_ARGS__) \
		instruction( FOR_EACH_WITH_COMMA(BOTH, __VA_ARGS__) ) \
			: base_instruction{ opcode::NAME } \
			FOR_EACH(INITIALIZATION, __VA_ARGS__) \
		{ \
		} \
		static instruction_info create_info() { return { opcode::NAME, COMMENT, { FOR_EACH_WITH_COMMA(ARGUMENT_META, __VA_ARGS__) } }; } \
		inline void execute(routine& routine)

#define U8(name) (uint8_t, name)
#define U16(name) (uint16_t, name)
#define S16(name) (int16_t, name)

#pragma pack(push, 1)

//--------------------------------------------------------------------------------------------

Ins(VALUE, "R(A) = INT(sBx)", U8(A), S16(sBx))
{
	routine.call_frame.stack[A].integer = sBx;
}};

Ins(LOADVAR, "PUSH = R(A)", U8(A))
{
	routine.push(routine.call_frame.stack[A]);
}};

Ins(SAVEVAR, "R(A) = POP", U8(A))
{
	routine.call_frame.stack[A] = routine.pop();
}};

//------------

Ins(ADD, "PUSH = POP + POP")
{
	routine.top[-2].integer = routine.top[-2].integer + routine.top[-1].integer;
	routine.top--;
}};

Ins(SUB, "PUSH = POP - POP")
{
	routine.top[-2].integer = routine.top[-2].integer - routine.top[-1].integer;
	routine.top--;
}};

Ins(MULT, "PUSH = POP * POP")
{
	routine.top[-2].integer = routine.top[-2].integer * routine.top[-1].integer;
	routine.top--;
}};

Ins(DIVIDE, "PUSH = POP / POP")
{
	routine.top[-2].integer = routine.top[-2].integer / routine.top[-1].integer;
	routine.top--;
}};

Ins(POWER, "PUSH = POP ^ POP")
{
	routine.top[-2].integer = std::pow(routine.top[-2].integer, routine.top[-1].integer);
	routine.top--;
}};

Ins(EQ, "PUSH = POP == POP")
{
	routine.top[-2].boolean = routine.top[-2].integer == routine.top[-1].integer;
	routine.top--;
}};

Ins(NEQ, "PUSH = POP != POP")
{
	routine.top[-2].boolean = routine.top[-2].integer != routine.top[-1].integer;
	routine.top--;
}};

Ins(L, "PUSH = POP < POP")
{
	routine.top[-2].boolean = routine.top[-2].integer < routine.top[-1].integer;
	routine.top--;
}};

Ins(G, "PUSH = POP > POP")
{
	routine.top[-2].boolean = routine.top[-2].integer > routine.top[-1].integer;
	routine.top--;
}};

Ins(LEQ, "PUSH = POP <= POP")
{
	routine.top[-2].boolean = routine.top[-2].integer <= routine.top[-1].integer;
	routine.top--;
}};

Ins(GEQ, "PUSH = POP >= POP")
{
	routine.top[-2].boolean = routine.top[-2].integer >= routine.top[-1].integer;
	routine.top--;
}};

//--------------

Ins(PUSH_K, "PUSH = K(A)", U8(A))
{
	routine.push(routine.call_frame.function->constant_buffer[A]);
}};

// ip already points to the next instruction, so offsets are relative to it
Ins(JUMP, "goto JMP(sBx)", S16(sBx))
{
	routine.call_frame.ip += sBx;
}};

Ins(IFJUMP, "if !(POP) then goto JMP(sBx)", S16(sBx))
{
	if (!routine.pop().boolean)
	{
		routine.call_frame.ip += sBx;
	}
}};

Ins(PRINT, "print POP")
{
	std::cout << routine.pop().integer << std::endl;
}};

Ins(CREATE_OBJECT, "R(A) = new CLS(Bx)", U8(A), U16(Bx))
{
	routine.call_frame.stack[A].object_index = routine.vm.object_storage.create_object(Bx);
}};

Ins(SET_FIELD, "R(A).FLD(B) = R(C)", U8(A), U8(B), U8(C))
{
	object_index object_index = routine.call_frame.stack[A].object_index;
	routine.vm.object_storage.get_object(object_index).data[B] = routine.call_frame.stack[C];
}};

Ins(VIRTUAL_CALL, "call FNC(B) with INT(A) args", U8(A), U8(B))
{
	cell* frame_start = &routine.call_frame.stack[-A];
	object_header& self = routine.vm.object_storage.get_object(frame_start->object_index);
	rt::user_class& self_class = routine.vm.type_registry.classes[self.class_index];
	rt::function& function = self_class.vtable[B];
	routine.push_call_frame(function, frame_start);
}};

Ins(INC, "R(A) += 1", U8(A))
{
	routine.call_frame.stack[A].integer++;
}};

Ins(END, "end")
{
	routine.stop();
}};

#pragma pack(pop)

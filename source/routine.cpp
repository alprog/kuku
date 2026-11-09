
#include "routine.h"
#include "base_instruction.h"
#include "virtual_machine.h"
#include "jump_table.h"

routine::routine(virtual_machine& vm, rt::function& function)
	: vm{ vm }
	, call_frame{ function, &stack.cells[0] }
{
	top = call_frame.stack + function.max_locals;
}

void routine::run()
{
	running = true;
	perform_instruction();
}

void routine::stop()
{
	running = false;
}

void routine::perform_instruction()
{
	while (running)
	{
		jump_table::execute_function[call_frame.ip->I](*this);
	}
}

void routine::push_call_frame(rt::function& function, cell* frame_start)
{
	up_frames.push(call_frame);
	call_frame = ::call_frame{ function, &stack.cells[0] };
}

void routine::pop_call_frame()
{
	call_frame = up_frames.top();
	up_frames.pop();
}
#pragma once

#include "symbol_table.h"
#include "chunk.h"
#include "stackable.h"
#include "scope_context.h"
#include "inline_operand.h"
#include "stack_ex.h"

class translation_module;

namespace stmt
{
	class symboled_statement_base;
}

class compiler
{
public:
	compiler(translation_module& module);

	void compile();
	void start_new_function(std::u16string name);
	void enter_scope(scope_type scope_type);
	void exit_scope();
	void define_local_variable(stmt::symboled_statement_base& statement);
	int define_local_variable(std::u16string name);
	
	template<typename T>
	void spawn(const T& instruction)
	{
		current_function->bytecode.write(instruction);
	}

	void spawn_jump_to_start();
	void spawn_jump_to_start(scope_context& scope_context);
	void spawn_jump_to_end();
	void spawn_jump_to_end(scope_context& scope_context);

	int get_current_place();

	scope_context& get_loop_context(int level = 1);
	scope_context& get_scope_context();

	template<typename T>
	void compile(T& value);

	chunk chunk;
	rt::function* current_function;

	stack_ex<::scope_context> scope_contexts;
	translation_module& module;
	symbol_table symbol_table;
};

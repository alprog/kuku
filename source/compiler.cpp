
#include "stmt/all.h"
#include "ast/all.h"
#include "compiler.h"
#include "translation_module.h"
#include "err/statement_error.h"
#include "bytecode.h"
#include "instructions.h"
#include <algorithm>

bool optimizations = false;

compiler::compiler(translation_module& module)
	: module{ module }
{
}

void compiler::compile()
{
	for (auto& statement : module.statements)
	{
		if (!statement->is_valid)
		{
			throw statement_error(*statement);
		}
	}
	
	scope_contexts.push_emplace(scope_type::module_root, 0, 0);

	for (auto& statement : module.statements)
	{
		compile(statement);
	}
}

void compiler::start_new_function(std::u16string name)
{
	current_function = &chunk.functions.emplace_back();
	current_function->name = name;
}

void compiler::enter_scope(scope_type scope_type)
{
	scope_contexts.push_emplace(scope_type, get_current_place(), get_scope_context().local_stack_size);
}

void compiler::exit_scope()
{
	for (auto& jump_place : get_scope_context().jump_to_end_places)
	{
		int jump_offset = get_current_place() - jump_place;
		reinterpret_cast<instruction_JUMP*>(&current_function->bytecode.instructions[jump_place])->sBx = jump_offset;
	}

	scope_contexts.pop();

	int new_stack_size = scope_contexts.top().local_stack_size;
	for (auto& local : current_function->locals)
	{
		if (local.end_instruction < 0 && local.stack_offset >= new_stack_size)
		{
			local.end_instruction = get_current_place() - 1;
		}
	}
}

void compiler::define_local_variable(stmt::symboled_statement_base& statement)
{
	auto variable_symbol = statement.get_symbol();
	variable_symbol->stack_offset = define_local_variable(variable_symbol->name);
}

int compiler::define_local_variable(std::u16string name)
{
	int stack_offset = get_scope_context().local_stack_size++;
	current_function->max_locals = std::max(current_function->max_locals, stack_offset + 1);

	rt::localvar_info info;
	info.name = name;
	info.stack_offset = stack_offset;
	info.type_index = type_index::Integer;
	info.start_instruction = get_current_place();
	info.end_instruction = -1;
	current_function->locals.push_back(info);

	return stack_offset;
}

void compiler::spawn(base_instruction instruction)
{
	current_function->bytecode.instructions.push_back(instruction);
}

void compiler::spawn_jump_to_start()
{
	spawn_jump_to_start(get_scope_context());
}

void compiler::spawn_jump_to_start(scope_context& scope_context)
{
	int offset = scope_context.start_place - get_current_place();
	spawn(instruction_JUMP(offset));
}

void compiler::spawn_jump_to_end()
{
	spawn_jump_to_end(get_scope_context());
}

void compiler::spawn_jump_to_end(scope_context& scope_context)
{
	scope_context.jump_to_end_places.push_back(get_current_place());
	spawn(instruction_JUMP(0));
}

base_instruction& compiler::peek()
{
	auto& instructions = current_function->bytecode.instructions;
	return instructions[instructions.size() - 1];
}

base_instruction compiler::pop()
{
	base_instruction result = peek();
	current_function->bytecode.instructions.pop_back();
	return result;
}

opcode opeartor_token_to_opcode(token_type token_type)
{
	switch (token_type)
	{
		case token_type::plus_operator:
			return opcode::ADD;

		case token_type::less_operator:
			return opcode::L;

		case token_type::minus_operator:
			return opcode::SUB;

		case token_type::multiply_Operator:
			return opcode::MULT;

		case token_type::divide_Operator:
			return opcode::DIVIDE;

		case token_type::exponent_operator:
			return opcode::POWER;

		case token_type::equal_operator:
			return opcode::EQ;

		case token_type::not_equal_operator:
			return opcode::NEQ;

		case token_type::greater_operator:
			return opcode::G;

		case token_type::less_or_equal_operator:
			return opcode::LEQ;

		case token_type::greater_or_equal_operator:
			return opcode::GEQ;

		default:
			throw std::exception("not implemented");
		}
}

int compiler::get_current_place()
{
	return current_function->bytecode.instructions.size();
}

scope_context& compiler::get_loop_context(int level)
{
	auto& elements = scope_contexts.elements;
	for (int i = elements.size() - 1; i >= 0; i--)
	{
		if (elements[i].scope_type == scope_type::loop_body)
		{
			if (--level == 0)
			{
				return elements[i];
			}
		}
	}
	throw std::exception("can't find loop context");
}

scope_context& compiler::get_scope_context()
{
	return scope_contexts.top(); 
}

//---------------------------------------------------------------------------------------------------------------

bool has_regA(opcode code)
{
	switch (code)
	{
		case opcode::VALUE:
			return true;
	}

	return false;
}

template<typename T>
void compiler::compile(T& value)
{
	value->compile(*this);
}

template<>
void compiler::compile(ast::integer_literal& literal)
{
	const int index = current_function->add_constant(literal.value);
	spawn(instruction_PUSH_K(index));
}

template<>
void compiler::compile(ast::string_literal& literal)
{
	// not implemented
}

template<>
void compiler::compile(ast::symbol_expression& expression)
{
	if (expression.reference.symbol != nullptr)
	{
		auto variable = dynamic_cast<variable_symbol*>(expression.reference.symbol);
		if (variable != nullptr)
		{
			spawn(instruction_LOADVAR(variable->stack_offset));
		}
	}
}

template<>
void compiler::compile(ast::binary_operator_expression& expression)
{
	base_instruction instruction;
	instruction.opcode = opeartor_token_to_opcode(expression.op.token_type);
	compile(expression.left);
	compile(expression.right);
	spawn(instruction);
}

template<>
void compiler::compile(stmt::variable_declaration_statement& statement)
{
	define_local_variable(statement);
	compile(statement.expression);
	spawn(instruction_SAVEVAR(statement.get_symbol()->stack_offset));
}

template<>
void compiler::compile(stmt::assign_statement& statement)
{
	auto symbol_expression = dynamic_cast<ast::symbol_expression*>(statement.lvalue.get());
	if (symbol_expression)
	{
		auto symbol = symbol_expression->reference.symbol;

		compile(statement.rvalue); // spawn src
		spawn(instruction_SAVEVAR(symbol->stack_offset));
	}
}

template<>
void compiler::compile(stmt::expression_statement& statement)
{
	compile(statement.expression);
}

template<>
void compiler::compile(stmt::function_statement& statement)
{
	start_new_function(statement.symbol->name);
	enter_scope(statement.inner_scope.type);
}

template<>
void compiler::compile(stmt::if_statement& statement)
{
	enter_scope(statement.inner_scope.type);

	auto size = get_scope_context().local_stack_size;

	compile(statement.condition);
	
	get_scope_context().jump_to_end_places.push_back(get_current_place());
	spawn(instruction_IFJUMP(0));
	
	
	get_scope_context().local_stack_size = size;
}

template<>
void compiler::compile(stmt::else_statement& statement)
{
	int jump_place = get_current_place();
	spawn(instruction_JUMP(0));

	exit_scope();
	enter_scope(statement.inner_scope.type);

	get_scope_context().jump_to_end_places.push_back(jump_place);
}

template<>
void compiler::compile(stmt::end_statement& statement)
{	
	if (get_scope_context().scope_type == scope_type::function_body)
	{
		spawn(instruction_END());
	}
	exit_scope();
}

template<>
void compiler::compile(stmt::while_statement& statement)
{
	enter_scope(statement.inner_scope.type);

	auto size = get_scope_context().local_stack_size;

	compile(statement.condition);
	
	get_scope_context().jump_to_end_places.push_back(get_current_place());
	spawn(instruction_IFJUMP(0));
	
	get_scope_context().local_stack_size = size;
}

template<>
void compiler::compile(stmt::for_statement& statement)
{
	enter_scope(statement.inner_scope.type);

	// counter (index)
	uint8_t index = (uint8_t)get_scope_context().local_stack_size;
	define_local_variable(statement);
	compile(statement.start_expression);
	spawn(instruction_SAVEVAR(index));

	// max_value (index + 1)
	define_local_variable(u"%max");
	compile(statement.end_expression);
	spawn(instruction_SAVEVAR(index + 1));


	spawn(instruction_JUMP(2));

	get_scope_context().start_place = get_current_place();

	// increment
	spawn(instruction_INC(index));

	// condition
	spawn(instruction_LOADVAR(index));
	spawn(instruction_LOADVAR(index + 1));
	spawn(instruction_LEQ());

	get_scope_context().jump_to_end_places.push_back(get_current_place());
	spawn(instruction_IFJUMP(0));
}

template<>
void compiler::compile(stmt::loop_statement& statement)
{
	spawn_jump_to_start();
	exit_scope();
}

template<>
void compiler::compile(stmt::continue_statement& statement)
{
	spawn_jump_to_start(get_loop_context(statement.level));
}

template<>
void compiler::compile(stmt::break_statement& statement)
{
	spawn_jump_to_end(get_loop_context(statement.level));
}

template<>
void compiler::compile(stmt::print_statement& statement)
{
	compile(statement.expression);
	spawn(instruction_PRINT());
}
#pragma once

#include <vector>
#include "lexer.h"
#include "statement_scope.h"
#include "compiler/ast/expression.h"
#include "binary_operator.h"
#include "compiler/ast/binary_operator_expression.h"

class symbol_reference;
class translation_module;
namespace stmt
{
	class statement;
}

class parser
{
public:
	parser(translation_module& module, token** it);
	void skip_empty_tokens();

	stmt::statement* parse_next_statement();
	std::unique_ptr<ast::expression> parse_expression();
	std::unique_ptr<ast::binary_operator_expression> parse_binary_operator_chain(std::unique_ptr<ast::expression> left_operand, binary_operator* current_operator);
	std::unique_ptr<ast::expression> parse_operand();
	binary_operator* match_binary_operator(precedence maximum_precedence, binary_operator*& out_operator);
	
	translation_module& module;
	token** it;
	token* current;
	
	bool match(token_type type);
	bool match_end_of_statement();

	void require(token_type type);
	void require_end_of_statement();

	symbol_reference read_symbol_reference();

	void next();
	std::vector<stmt::statement*> statements;

	template <typename T>
	T* create_statement(token* start_token = nullptr);

	template <typename T>
	T* create_statement(token* start_token, std::unique_ptr<ast::expression> expression);
};

#pragma once

#include <vector>
#include "text_document.h"
#include "token.h"
#include "stmt/statement.h"
#include "lsp/diagnostic.h"
#include "bytecode.h"
#include "chunk.h"

class source_project;

class translation_module
{
public:
	translation_module(source_project& project, std::string uri, input_stream<utf16unit>& stream);
	~translation_module();

	void process();

	void tokenize();
	void parse_statements();
	void analyze_scope();
	void analyze_semantic();
	void compile();
	chunk compile_to_chunk();
	
	void set_statement_to_tokens();
	void clear();

	void print_statements();
	std::vector<lsp::diagnostic> get_diagnostics();

	token* get_token(lsp::position position);
	stmt::statement* get_statement(lsp::position position);

	source_project& project;

	std::string uri;
	text_document document;
	std::vector<token*> tokens; // own
	std::vector<stmt::statement*> statements; // own

	statement_scope root_scope;

};
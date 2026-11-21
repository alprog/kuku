
#pragma once

#include <map>
#include "translation_module.h"
#include "symbol_table.h"

class source_project
{
public:
	~source_project();

	void add_file(std::string uri);
	void add_file(std::string uri, std::u8string content);
	void add_file(std::string uri, std::u16string content);
	void add_memory_snippet(std::u16string snippet);

	void update_workspace_folder(std::string uri, bool added);

	void process_all();
	void clear_all();

	void print_info();

	translation_module* get_module(std::string uri);

	//symbol_table symbol_table;
private:
	std::map<std::string, translation_module*> modules;
};  

#include "source_project.h"
#include "unicode/unicode_streams.h"

source_project::~source_project()
{
	clear_all();
}

void source_project::add_file(std::string uri)
{
	basic_input_stream basic_stream{ new std::basic_ifstream<utf8unit> { uri } };
	unicode::utf8to16_stream u16stream(basic_stream);
	modules[uri] = new translation_module(*this, uri, u16stream);
}

void source_project::add_file(std::string uri, std::u8string content)
{
	basic_input_stream basic_stream{ new std::basic_istringstream{ content} };
	unicode::utf8to16_stream u16stream{ basic_stream };
	modules[uri] = new translation_module(*this, uri, u16stream);
}

void source_project::add_file(std::string uri, std::u16string content)
{
	basic_input_stream u16stream{ new std::basic_istringstream{ content } };
	modules[uri] = new translation_module(*this, uri, u16stream);
}

void source_project::add_memory_snippet(std::u16string line)
{
	basic_input_stream basic_stream{ new std::basic_istringstream{ line } };
	
	modules["memory"] = new translation_module(*this, "memory", basic_stream);
}

void source_project::update_workspace_folder(std::string uri, bool added)
{
}

void source_project::process_all()
{
	for (auto& pair : modules)
	{
		pair.second->process();
	}
}

void source_project::clear_all()
{
	for (auto& pair : modules)
	{
		delete pair.second;
	}
	modules.clear();
}

void source_project::print_info()
{
	for (auto& pair : modules)
	{
		pair.second->print_statements();
	}
}

translation_module* source_project::get_module(std::string uri)
{
	auto it = modules.find(uri);
	if (it != std::end(modules))
	{
		return it->second;
	}
	return nullptr;
}
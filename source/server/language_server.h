#pragma once

#include <string>
#include "core/json/object.h"
#include "ide_connection.h"
#include "compiler/source_project.h"

class language_server
{
public:
	language_server();

private:
	void process_message(json::object& message);
	void on_initialize(json::object& message);
	void on_did_change_workspace_folders(json::object& message);
	void on_did_open(json::object& message);
	void on_did_change(json::object& message);
	void on_hover(json::object& message);
	void on_code_action(json::object& message);
	void on_execute_with_command(json::object& message);
	void on_completion(json::object& message);

	void show_message(std::string text);
	void publish_diagnostics(translation_module& module);
	void update_workspace_folders(json::object& folders, bool added);

	source_project source_project;
	Ide_connection ide_connection;
};
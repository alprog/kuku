
#include "language_server.h"

#include <iostream>
#include <fstream>
#include "types.h"
#include "lsp/enums.h"
#include "lsp/text_document_item.h"
#include "unicode/unicode.h"
#include "lsp/did_change_text_document_params.h"

language_server::language_server()
{
	while (true)
	{
		json::object message;
		ide_connection >> message;
		process_message(message);
	}
}

void language_server::process_message(json::object& message)
{
    auto method = message["method"].get<std::string>();

    if (method == "initialize")
        on_initialize(message);
    else if (method == "initialized")
        {} // nothing to do
    else if (method == "textDocument/didOpen")
        on_did_open(message);
    else if (method == "textDocument/didChange")
        on_did_change(message);
    else if (method == "textDocument/hover")
        on_hover(message);
    else if (method == "textDocument/codeAction")
        on_code_action(message);
    else if (method == "workspace/executeCommand")
        on_execute_with_command(message);
    else if (method == "workspace/didChangeWorkspaceFolders")
        on_did_change_workspace_folders(message);
    else if (method == "textDocument/completion")
        on_completion(message);
    else if (method == "$/cancelRequest")
        {} // nothing to do
    else
        throw new std::exception("unknown method");
}

void language_server::on_initialize(json::object& message)
{
    auto name = message["params"]["clientInfo"]["name"].get<std::string>();

    auto& folders = message["params"]["workspaceFolders"];
    if (folders.is_array())
    {
        update_workspace_folders(folders, true);
    }

    auto id = message["id"].get<int>();

    json::object result = {
        { "capabilities", {
            { "textDocumentSync", lsp::text_document_sync_kind::Incremental },
            { "completionProvider", {
                { "resolveProvider", true }
            }},
            { "workspace", {
                { "workspaceFolders", {
                    { "supported", true },
                    { "changeNotifications", true }
                }}
            }},
            { "hoverProvider", true },
            { "executeCommandProvider", {
                { "commands", { "kuku.test", "kuku.a", "kuku.b", "kuku.c"}}
            }},
            { "codeActionProvider", {
                { "codeActionKinds", { 
                    "refactor.extract.function",
                    "refactor.extract.line",
                    "source.fixAll",
                    "source.c"
                }},
                { "resolveProvider", false }
            }}
        }}
    };

    json::object response = {
        { "jsonrpc", "2.0" },
        { "id", id },
        { "result", result }
    };

    ide_connection << response;
}

void language_server::on_did_change_workspace_folders(json::object& message)
{
    auto& event = message["params"]["event"];
    update_workspace_folders(event["removed"], false);
    update_workspace_folders(event["added"], true);
}

void language_server::on_did_open(json::object& message)
{
    auto json = message["params"]["textDocument"];
    auto document = from_json<lsp::text_document_item>(json);

    source_project.add_file(document.uri, document.text);
    source_project.process_all();

    publish_diagnostics(*source_project.get_module(document.uri));
}

void language_server::on_did_change(json::object& message)
{
    auto params = from_json<lsp::did_change_text_document_params>(message["params"]);
    auto uri = params.text_document.uri;
    auto module = source_project.get_module(uri);
    if (module != nullptr)
    {
        for (auto& change : params.content_changes)
        {
            module->document.change_content(change);
        }
        module->clear();
        module->process();
        publish_diagnostics(*module);
    }
}

void language_server::on_hover(json::object& message)
{
    auto id = message["id"].get<int>();
    auto uri = message["params"]["textDocument"]["uri"].get<std::string>();
   
    
    auto line = message["params"]["position"]["line"].get<int>();
    auto character = message["params"]["position"]["character"].get<int>();
    auto position = lsp::position(line, character);

    json::object result = nullptr;

    auto module = source_project.get_module(uri);
    if (module != nullptr)
    {
        token* token = module->get_token(position);
		if (token != nullptr)
		{
            auto hover_text = token->get_hover_text();

            stmt::statement* statement = token->statement;
            if (statement != nullptr)
            {
                hover_text += u"  \r\n" + statement->get_hover_text();
            }

            result = {
                { "contents", unicode::to_utf8(hover_text) }
            };
		}
    }

    json::object response = {
        { "jsonrpc", "2.0" },
        { "id", id },
        { "result", result }
    };

    ide_connection << response;
}

void language_server::on_code_action(json::object& message)
{
    /*
        "textDocument": {
            "uri": "file:///c%3A/kuku/data/main.kuku"
        },
        "range" : {
            "start": {
                "line": 17,
                "character" : 16
            },
            "end" : {
                "line": 17,
                "character" : 16
            }
        },
        "context": {
            "diagnostics": []
        }
    */

    auto id = message["id"].get<int>();

    json::object result = {
        /*{
            { "title", "extract function" },
            { "kind", "refactor.extract.function" },
            { "command", {
                { "title", "CommandA" },
                { "command", "kuku.a" }
            }},
            {"diagnostics", {
                {
                    { "severity", 4 },

                    { "tags", { 1 } },

                    { "message", "bla-bla" },

                    { "range", {
                        { "start", {
                            { "line", 1 },
                            { "character", 1 },
                        }},
                        { "end", {
                            { "line", 1 },
                            { "character", 1 },
                        }}
                    }}
                }
            }}
        },
        {
            { "title", "extract line" },
            { "kind", "refactor.extract.line" },
            { "command", {
                { "title", "CommandB" },
                { "command", "b" },
            }},
            { "disabled", {{ "reason", "just because" }}}
        },*/
        {
            { "title", "organizeImports" },
            { "kind", "source.organizeImports" },
            { "command", {
                { "title", "CommandB" },
                { "command", "kuku.b" }
            }},
        },
        {
            { "title", "Command C" },
            { "kind", "source.c" },
            { "command", {
                { "title", "CommandC" },
                { "command", "kuku.c" }
            }},
        },
    };

    json::object response = {
        { "jsonrpc", "2.0" },
        { "id", id },
        { "result", result }
    };

    ide_connection << response;
}

void language_server::on_execute_with_command(json::object& message)
{
    auto id = message["id"].get<int>();
    auto command_name = message["params"]["command"].get<std::string>();

    show_message("command " + command_name + " was performed!");

    json::object response = {
        { "jsonrpc", "2.0" },
        { "id", id },
        { "result", 0 }
    };

    ide_connection << response;
}

void language_server::on_completion(json::object& message)
{
    /*
       "textDocument": {
           "uri": "file:///c%3A/Users/alpro/Desktop/2.txt",
           "version": 4
       },
       "contentChanges": [
           {
               "range": {
                   "start": {
                       "line": 5,
                       "character": 1
                   },
                   "end": {
                       "line": 5,
                       "character": 1
                   }
               },
               "rangeLength": 0,
               "text": "A"
           }
       ]
   */
}

void language_server::show_message(std::string text)
{
    json::object params = {
        { "type", lsp::diagnostic_severity::Information },
        { "message", text }
    };

    json::object notification = {
        { "jsonrpc", "2.0" },
        { "method", "window/showMessage" },
        { "params", params }
    };

    ide_connection << notification;
}

void language_server::publish_diagnostics(translation_module& module)
{
    auto array = nlohmann::json::array();
    for (auto& diagnostic : module.get_diagnostics())
    {
        array.push_back(diagnostic.to_json());
    }

    json::object params = {
        { "uri", module.uri },
        { "diagnostics", array }
    };

    json::object notification = {
        { "jsonrpc", "2.0" },
        { "method", "textDocument/publishDiagnostics" },
        { "params", params }
    };

    ide_connection << notification;
}

void language_server::update_workspace_folders(json::object& folders, bool added)
{
    for (auto& folder : folders)
    {
        source_project.update_workspace_folder(folder["uri"].get<std::string>(), added);
    }
}

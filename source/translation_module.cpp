
#include "translation_module.h"

#include "source_project.h"
#include "console.h"
#include "scope_analyzer.h"
#include "semantic_analyzer.h"
#include "export_creator.h"
#include "compiler.h"
#include "err/error.h"

translation_module::translation_module(source_project& project, std::string uri, input_stream<utf16unit>& stream)
	: project{ project }
	, uri{ uri }
	, document{ stream }
	, root_scope{ nullptr, scope_type::module_root }
{
}

translation_module::~translation_module()
{
    clear();
}

void translation_module::process()
{
    tokenize();
    parse_statements();
    analyze_scope();
    create_export();
    analyze_semantic();
}

void translation_module::tokenize()
{
	lexer lexer(document);
    while (true)
    {
        auto token = lexer.get_next_token();
        tokens.push_back(token);
        if (token->type == token_type::end_of_source)
        {
            break;
        }
    }
}

void translation_module::parse_statements()
{
    parser parser(*this, &tokens[0]);
    while (true)
    {
        auto statement = parser.parse_next_statement();
        if (statement == nullptr) break;
        statements.push_back(statement);
    }

    set_statement_to_tokens();
}

void translation_module::set_statement_to_tokens()
{
    auto index = 0;
    for (auto& statement : statements)
    {
        while (tokens[index] != statement->start_token)
        {
            tokens[index++]->statement = nullptr;
        }
        while (tokens[index] != statement->end_token)
        {
            tokens[index++]->statement = statement;
        }
        tokens[index++]->statement = statement;
    }
    while (index < tokens.size())
    {
        tokens[index++]->statement = nullptr;
    }
}

void translation_module::analyze_scope()
{
    scope_analyzer analyzer(*this);
    analyzer.analyze();
}

void translation_module::create_export()
{
    export_creator creator(*this);
    export_text = creator.create();
}

void translation_module::analyze_semantic()
{
    semantic_analyzer analyzer(*this);
    analyzer.analyze();
}

void translation_module::compile()
{
    compiler compiler(*this);
    compiler.compile();
}

chunk translation_module::compile_to_chunk()
{
    try
    {
        compiler compiler(*this);
        compiler.compile();
        return compiler.chunk;
    }
    catch (error& error)
    {
        console::write_line(error.get_message());
    }

    return chunk();
}

void translation_module::clear()
{
    root_scope.clear();
    for (auto& token : tokens)
    {
        delete token;
    }
    tokens.clear();
    for (auto& statement : statements)
    {
        delete statement;
    }
    statements.clear();
}

void translation_module::print_statements()
{
    for (auto statement : statements)
    {
        auto line = statement->get_statement_type() + u" " + (statement->is_valid ? u"1" : u"0");
        console::write_line(line);

        if (!statement->is_valid)
        {
            console::write_line(statement->error_text);
        }
    }
}

std::vector<lsp::diagnostic> translation_module::get_diagnostics()
{
    std::vector<lsp::diagnostic> result;
    for (auto& statement : statements)
    {
        for (auto& diagnosic : statement->diagnostics)
        {
            result.push_back(diagnosic);
        }
    }
    return result;
}

token* translation_module::get_token(lsp::position position)
{
    for (auto token : tokens)
    {
        if (token->range.contains(position))
        {
            return token;
        }
    }
    return nullptr;
}

stmt::statement* translation_module::get_statement(lsp::position position)
{
    for (auto statement : statements)
    {
        if (statement->get_full_range().contains(position))
        {
            return statement;
        }
    }
    return nullptr;
}
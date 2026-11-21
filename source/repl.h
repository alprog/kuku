#pragma once

#include <iostream>
#include "lexer.h";
#include "core/console.h"
#include "core/types.h"
#include "core/unicode/unicode.h"
#include "text_document.h"
#include <sstream>

#include "source_project.h"
#include "virtual_machine.h"
#include "bytecode.h"

void repl() // read–eval–print loop
{
    std::cout << "kuku language 0.1" << std::endl;
    
    virtual_machine machine;

    while (true)
    {
        std::cout << "> ";
        std::u16string line = console::read_line();
        if (line == u"exit")
        {
            break;
        }
        
        source_project project;
        project.add_memory_snippet(line);
        project.process_all();

        chunk chunk = project.get_module("memory")->compile_to_chunk();

        auto& routine = machine.create_routine(chunk.functions[0]);
        routine.run();        

        project.clear_all();
    }
}

#include "test.h"

#include "streams.h"
#include "unicode_streams.h"
#include "text_document.h"
#include <fstream>
#include "parser.h"

#include "virtual_machine.h"
#include "string.h"
#include "bytecode.h"
#include "opcode.h"
#include "routine.h"

#include "source_project.h"

#include "mem/tracker.h"
#include "instructions.h"
#include <memory>
#include "base64.h"
#include "guid.h"

#include "console.h"

void test()
{
	while (true)
	{
		virtual_machine machine;

		source_project project;
		project.add_file("C:/projects/kuku/data/test.kuku");
		project.process_all();

		chunk chunk = project.get_module("C:/projects/kuku/data/test.kuku")->compile_to_chunk();

		for (auto& function : chunk.functions)
		{
			function.full_dump();

			console::new_line();
		}

		console::read_line();

		auto& routine = machine.create_routine(chunk.functions[0]);
		routine.run();

		console::read_line();
	}
}
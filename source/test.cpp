
#include "test.h"

#include "core/streams.h"
#include "core/unicode/unicode_streams.h"
#include "text_document.h"
#include <fstream>
#include "parser.h"

#include "vm/virtual_machine.h"
#include "string.h"
#include "vm/bytecode.h"
#include "vm/opcode.h"
#include "vm/routine.h"

#include "source_project.h"

#include "core/mem/tracker.h"
#include "vm/instructions.h"
#include <memory>
#include "core/base64.h"
#include "core/guid.h"

#include "core/console.h"
#include "vm/export_loader.h"
#include "imgui_window.h"

void test()
{
	start_imgui_window();

	while (true)
	{
		virtual_machine machine;

		std::string test_file_path = "C:/projects/kuku/data/main.kuku";

		source_project project;
		project.add_file(test_file_path);
		project.process_all();



		chunk chunk = project.get_module(test_file_path)->compile_to_chunk();

		for (auto& function : chunk.functions)
		{
			function.full_dump();

			console::new_line();
		}

		export_loader(machine.type_registry).load_test();

		console::write_line(project.get_module(test_file_path)->export_text);
		console::read_line();

		auto& routine = machine.create_routine(chunk.functions[0]);
		routine.run();

		console::read_line();
	}
}
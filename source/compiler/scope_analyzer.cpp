
#include "scope_analyzer.h"
#include "statement_scope.h"
#include "compiler/stmt/all.h"
#include "translation_module.h"
#include "source_project.h"

scope_analyzer::scope_analyzer(translation_module& module)
	: module{ module }
{
}

void scope_analyzer::analyze()
{
	auto current_scope = &module.root_scope;
	
	for (int i = 0; i < module.statements.size(); i++)
	{
		auto statement = module.statements[i];

		statement->sequence_number = i;
		statement->set_scope(current_scope);

		auto allowed_scope_types = statement->get_allowed_scopes();
		if ((allowed_scope_types & current_scope->type) == scope_type::none)
		{
			statement->is_valid = false;
			statement->error_text = u"not valid scope";
			continue;
		}

		auto symboled_statement = dynamic_cast<stmt::symboled_statement_base*>(statement);
		if (symboled_statement)
		{
			current_scope->define_symbol(symboled_statement->get_symbol());
		}
		
		if (dynamic_cast<stmt::end_statement*>(statement) || dynamic_cast<stmt::loop_statement*>(statement) || dynamic_cast<stmt::else_statement*>(statement))
		{
			current_scope = current_scope->get_parent();
		}

		auto scoped_statement = dynamic_cast<stmt::scoped_statement_base*>(statement);
		if (scoped_statement)
		{
			current_scope = &scoped_statement->inner_scope;
		}
	}
}
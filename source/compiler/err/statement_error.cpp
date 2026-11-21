
#include "statement_error.h"

statement_error::statement_error(stmt::statement& statement)
	: statement {statement}
{
}

std::u16string statement_error::get_message()
{
	return statement.error_text;
}
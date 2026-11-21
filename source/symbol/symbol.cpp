
#include "symbol.h"

#include "vm/symbol_table.h"
#include "symbol_reference.h"
#include "token.h"

symbol::symbol(symbol_reference& definition)
	: definition { &definition }
{
	name = definition.token->get_source_text();
}

symbol::~symbol()
{

}

#include "virtual_machine.h"
#include "jump_table.h"

virtual_machine::virtual_machine()
    : object_storage { *this }
{
    jump_table::init();
}

routine& virtual_machine::create_routine(rt::function& function)
{
    return routines.emplace_back(*this, function);
}
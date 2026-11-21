
#include "instance.h"
#include "cell.h"
#include "vm/rt/user_class.h"

void instance::dump()
{
    cells[0].class_pointer->dump(*this);
}
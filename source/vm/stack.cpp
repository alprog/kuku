
#include "stack.h"

stack::stack()
{
    cells.resize(1024 * 1024 / sizeof(cell)); // 1 MB
}
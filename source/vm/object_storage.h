
#pragma once

#include <vector>
#include <stack>
#include "object_header.h"

class virtual_machine;

class object_storage
{
public:
    explicit object_storage(virtual_machine& vm);

    object_header& get_object(object_index object_index);  
    object_index create_object(class_index class_index);

private:
    void destroy_object(object_index object_index);

    virtual_machine& vm;
    std::vector<object_header> objects;
    std::stack<object_index> holes;
};
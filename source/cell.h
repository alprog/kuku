#pragma once

#include "core/types.h"
#include "instance.h"
#include "kuku/string.h"

namespace rt
{
    class user_class;
}

union cell
{
    cell() = default;
    cell(int integer);

    bool boolean;
    byte byte;
    integer integer;
    number number;
    object_index object_index;
    kuku::string* string;
    rt::user_class* class_pointer;

    std::strong_ordering operator<=>(const cell& other) const;
    bool operator==(const cell& other) const;
    bool operator!=(const cell& other) const;
};
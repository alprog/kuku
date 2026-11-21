#pragma once

union cell;

struct instance
{
public:
    void dump();

    cell* cells;
};
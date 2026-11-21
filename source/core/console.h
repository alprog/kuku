#pragma once

#include <string>
#include <conio.h>

namespace console
{
    std::u16string read_line();

    void write(std::string str);
    void write(std::u8string str);
    void write(std::u16string str);
    void write_line(std::string line);
    void write_line(std::u8string line);
    void write_line(std::u16string line);
    void new_line();
}

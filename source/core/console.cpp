
#include "console.h"

namespace console
{
    std::u16string read_line()
    {
        wchar_t buffer[0x1000];
        std::size_t num_read = 0;
        _cgetws_s(buffer, &num_read);
        std::wstring line(buffer, num_read);
        return std::u16string(std::begin(line), std::end(line));
    }

    void write(std::string str)
    {
        _cputws(std::wstring(std::begin(str), std::end(str)).c_str());
    }

    void write(std::u8string str)
    {
        _cputws(std::wstring(std::begin(str), std::end(str)).c_str());
    }

    void write(std::u16string str)
    {
        _cputws(std::wstring(std::begin(str), std::end(str)).c_str());
    } 

    void write_line(std::string line)
    {
        _cputws(std::wstring(std::begin(line), std::end(line)).c_str());
        _cputws(L"\n");
    }

    void write_line(std::u8string line)
    {
        _cputws(std::wstring(std::begin(line), std::end(line)).c_str());
        _cputws(L"\n");
    }

    void write_line(std::u16string line)
    {
        _cputws(std::wstring(std::begin(line), std::end(line)).c_str());
        _cputws(L"\n");
    }

    void new_line()
    {
        _cputws(L"\n");
    }
}

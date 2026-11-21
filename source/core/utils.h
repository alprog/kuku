#pragma once

#include <string>
#include <vector>

template <typename StringT>
std::vector<StringT> split(StringT line, StringT delimeter)
{
    std::vector<StringT> result;

    size_t start = 0;
    size_t index = line.find(delimeter);
    while (index != StringT::npos)
    {
        result.push_back(line.substr(start, index - start));
        start = index + delimeter.size();
        index = line.find(delimeter, start);
    }
    if (start <= line.size())
    {
        result.push_back(line.substr(start));
    }

    return result;
}
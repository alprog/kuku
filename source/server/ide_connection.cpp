
#include "ide_connection.h"
#include <iostream>
#include <string>

Ide_connection& operator>>(Ide_connection& ide, json::object& message)
{
    std::string line;

    getline(std::cin, line);
    auto index = line.find(':');
    auto count = std::atoi(line.substr(index + 1).c_str());

    getline(std::cin, line);

    std::string content_text;
    content_text.resize(count, 'x');
    std::cin.read(&content_text[0], count);

    message = json::object::parse(content_text);

    return ide;
}

Ide_connection& operator<<(Ide_connection& ide, json::object& message)
{
    auto content_text = message.dump();

    const auto content_length = content_text.size();
    constexpr auto content_type = "utf-8";

    static std::string line_ending = "\n";

    // header
    std::cout << "Content-Length: " << std::to_string(content_length) << line_ending;
    std::cout << "Content-Type: " << content_type << line_ending;

    std::cout << line_ending; // separator

    // content
    std::cout << content_text;

    std::cout.flush();

    return ide;
}
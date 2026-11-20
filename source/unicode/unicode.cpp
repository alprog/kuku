
#include "unicode.h"
#include "cell.h"

constexpr int COUNT_7_BIT = 128;
constexpr int COUNT_11_BIT = 2048;
constexpr int COUNT_16_BIT = 65536;

constexpr utf8unit HAS_2_OCTETS = 0b11000000;
constexpr utf8unit HAS_3_OCTETS = 0b11100000;
constexpr utf8unit HAS_4_OCTETS = 0b11110000;
constexpr utf8unit CONTINUATION = 0b10000000;

bool unicode::read_character(input_stream<utf8unit>& stream, character& character)
{
    utf8unit byte;
    if (!stream.read(byte)) return false;
    if (byte < 128)
    {
        character = byte;
        return true;
    }

    int continuation_count;
    if (byte >= HAS_4_OCTETS)
    {
        character = byte & 0b111; // 3 bits
        continuation_count = 3;
    }
    else if (byte >= HAS_3_OCTETS)
    {
        character = byte & 0b1111; // 4 bits
        continuation_count = 2;
    }
    else if (byte >= HAS_2_OCTETS)
    {
        character = byte & 0b11111; // 5 bits
        continuation_count = 1;
    }
    else
    {
        return false;
    }

    while (continuation_count > 0)
    {
        if (!stream.read(byte)) return false;

        if ((byte & 0b11000000) == CONTINUATION)
        {
            character = (character << 6) + (byte & 0b00111111);
            continuation_count--;
        }
        else
        {
            return false;
        }
    }

    return true;
}

void unicode::write_character(output_stream<utf8unit>& stream, character character)
{
    if (character < COUNT_7_BIT)
    {
        stream.write(character);
    }
    else if (character < COUNT_11_BIT)
    {
        stream.write((character >> 6) & 0b00011111 | HAS_2_OCTETS); // 5
        stream.write((character >> 0) & 0b00111111 | CONTINUATION); // 6
    }
    else if (character < COUNT_16_BIT)
    {
        stream.write((character >> 12) & 0b00001111 | HAS_3_OCTETS); // 4
        stream.write((character >> 06) & 0b00111111 | CONTINUATION); // 6
        stream.write((character >> 00) & 0b00111111 | CONTINUATION); // 6
    }
    else // 21 bit
    {
        stream.write((character >> 18) & 0b00000111 | HAS_4_OCTETS); // 3
        stream.write((character >> 12) & 0b00111111 | CONTINUATION); // 6
        stream.write((character >> 06) & 0b00111111 | CONTINUATION); // 6
        stream.write((character >> 00) & 0b00111111 | CONTINUATION); // 6
    }
}

constexpr utf16unit SURROGATES_START = 0xD800;
constexpr utf16unit SURROGATES_HALF = 0xDC00;
constexpr utf16unit SURROGATES_END = 0xE000;

bool unicode::read_character(input_stream<utf16unit>& stream, character& result)
{
    utf16unit first_unit;
    if (!stream.read(first_unit))
    {
        return false;
    }

    if (first_unit < SURROGATES_START || first_unit >= SURROGATES_END)
    {
        result = first_unit;
        return true;
    }

    utf16unit second_unit;
    if (stream.read(second_unit))
    {
        return false;
    }

    auto high_bits = (character)(first_unit - SURROGATES_START) << 10;
    auto low_bits = (character)(second_unit - SURROGATES_END);
    result = high_bits + low_bits + COUNT_16_BIT;
    return true;
}

void unicode::write_character(output_stream<utf16unit>& stream, character character)
{
    if (character < COUNT_16_BIT)
    {
        if (character >= SURROGATES_START && character < SURROGATES_END)
        {
            throw std::exception("can't write surrogate pair as utf-16");
        }
        else
        {
            stream.write(character);
        }
    }
    else
    {
        auto remainder = character - COUNT_16_BIT; // 20-bit remainder
        auto w1 = SURROGATES_START + (remainder >> 10);         // high 10 bits
        auto w2 = SURROGATES_HALF + (remainder & 0b1111111111); // low 10 bits
        stream.write(w1);
        stream.write(w2);
    }
}

template <typename InT, typename OutT>
void convert(input_stream<InT>& input_stream, output_stream<OutT>& output_stream)
{
    character character;
    while (unicode::read_character(input_stream, character))
    {
        unicode::write_character(output_stream, character);
    }
}

std::u8string unicode::to_utf8(const std::u16string& input_string)
{
    basic_input_stream input_stream{ new std::basic_istringstream { input_string } };
    string_output_stream<utf8unit> output_stream;
    convert(input_stream, output_stream);
    return output_stream.string_stream.str();
}

std::u16string unicode::to_utf16(const std::u8string& input_string)
{
    basic_input_stream input_stream{ new std::basic_istringstream { input_string } };
    string_output_stream<utf16unit> output_stream;
    convert(input_stream, output_stream);
    return output_stream.string_stream.str();
}

std::u8string operator ""_s(const char8_t* pointer, size_t size)
{
    return std::u8string(pointer);
}

std::u16string operator ""_s(const char16_t* pointer, size_t size)
{
    return std::u16string(pointer);
}
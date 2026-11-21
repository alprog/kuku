
#include "base64.h"

std::string& get_alphabet()
{
	static std::string alphabet = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
	return alphabet;
}

std::vector<byte> create_bit_table()
{
	std::vector<byte> table(256);
	int bitmask = 0;
	for (auto c : get_alphabet())
	{
		table[c] = bitmask++;
	}
	return table;
}

inline character get_character(byte bits)
{
	return get_alphabet()[bits];
}

byte get_bits(char character)
{
	static std::vector<byte> bit_table = create_bit_table();
	return bit_table[character];
}

struct block24
{
	unsigned int a : 6;
	unsigned int b : 6;
	unsigned int c : 6;
	unsigned int d : 6;
};

void base64::convert_4_characters_to_3_bytes(char* characters, byte* bytes)
{
	block24* block = reinterpret_cast<block24*>(bytes);
	block->a = get_bits(characters[0]);
	block->b = get_bits(characters[1]);
	block->c = get_bits(characters[2]);
	block->d = get_bits(characters[3]);
}

void base64::convert_3_bytes_to_4_characters(byte* bytes, char* characters)
{
	block24* block = reinterpret_cast<block24*>(bytes);
	characters[0] = get_character(block->a);
	characters[1] = get_character(block->b);
	characters[2] = get_character(block->c);
	characters[3] = get_character(block->d);
}
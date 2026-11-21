
#include "string.h"

kuku::string::string(int32_t character_count, byte character_size, void* src_bytes)
	: character_count{ character_count }
	, character_size{ character_size }
{
	auto size = character_count * character_size;
	bytes = new byte[size];
	memcpy(bytes, src_bytes, size);
}

kuku::string::string(std::string u8string)
	: string{ (int32_t)u8string.size(), 1, &u8string[0] }
{
}

kuku::string::string(std::u16string u16string)
	: string{ (int32_t)u16string.size(), 2, &u16string[0] }
{
}

kuku::string::string(std::u32string u32string)
	: string{ (int32_t)u32string.size(), 4, &u32string[0] }
{
}

kuku::string::~string()
{
	delete[] bytes;
}

character kuku::string::get_character(integer index)
{
	switch (character_size)
	{
		default:
		case 1:
			return bytes[index];
		case 2:
			return units[index];
		case 4:
			return characters[index];
	}
}

int kuku::string::get_largest_character_size()
{
	switch (character_size)
	{
		default:
		case 1:
			return 1;

		case 2:
			for (int i = 0; i < character_count; i++)
			{
				if (units[i] >= 256)
				{
					return 2;
				}
			}
			return 1;

		case 4:
			int max = 1;
			for (int i = 0; i < character_count; i++)
			{
				if (characters[i] >= 65536)
				{
					return 4;
				}
				else if (characters[i] >= 256)
				{
					max = 2;
				}
			}
			return max;
	}	
}

void kuku::string::try_shrink()
{
	change_character_size(get_largest_character_size());
}

void kuku::string::change_character_size(int new_character_size)
{
	if (new_character_size == character_size)
	{
		return;
	}

	auto new_bytes = new byte[character_count * new_character_size];

	if (new_character_size == 1)
	{
		if (character_size == 2)
		{
			for (int i = 0; i < character_count; i++)
			{
				new_bytes[i] = static_cast<byte>(units[i]);
			}
		}
		else /* character_size == 4 */
		{
			for (int i = 0; i < character_count; i++)
			{
				new_bytes[i] = static_cast<byte>(characters[i]);
			}
		}
	}
	else if ( new_character_size == 2 )
	{
		utf16unit* new_units = reinterpret_cast<utf16unit*>(new_bytes);
		if (character_size == 1)
		{
			for (int i = 0; i < character_count; i++)
			{
				new_units[i] = bytes[i];
			}
		}
		else /* character_size == 4 */
		{
			for (int i = 0; i < character_count; i++)
			{
				new_units[i] = static_cast<utf16unit>(characters[i]);
			}
		}
	}
	else /* new_character_size == 4 */
	{
		character* new_characters = reinterpret_cast<character*>(new_bytes);
		if (character_size == 1)
		{
			for (int i = 0; i < character_count; i++)
			{
				new_characters[i] = bytes[i];
			}
		}
		else /* character_size == 2 */
		{
			for (int i = 0; i < character_count; i++)
			{
				new_characters[i] = units[i];
			}
		}
	}

	delete[] bytes;
	bytes = new_bytes;
	character_size = new_character_size;
}
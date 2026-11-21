#pragma once

#include "core/types.h"
#include <string>

namespace kuku
{
	class string
	{
	private:
		string(int32_t character_count, byte character_size, void* src_bytes);

	public:
		string(std::string u8string);
		string(std::u16string u16string);
		string(std::u32string u32string);
		~string();

		character get_character(integer index);

		int get_largest_character_size();
		void try_shrink();
		void change_character_size(int new_character_size);

		int32_t character_count;
		byte character_size;

		union 
		{
			byte* bytes;
			utf16unit* units;
			character* characters;
		};
	};
}

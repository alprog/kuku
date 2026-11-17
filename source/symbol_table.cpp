
#include "symbol_table.h"

#define XXH_INLINE_ALL
#include "xxhash.h"

uint64_t symbol_table::getHash(const std::string& name) const
{
	return XXH3_64bits(name.data(), name.size());
}

uint16_t symbol_table::getValue(const std::string& name) const
{
	return getValue(getHash(name));
}

uint16_t symbol_table::getValue(uint64_t hash) const
{
	auto it = symbol_table.find(hash);
	return it != std::end(symbol_table) ? it->second : -1;
}

void symbol_table::setValue(uint64_t hash, uint16_t value)
{
	symbol_table[hash] = value;
}
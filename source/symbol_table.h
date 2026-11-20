#pragma once

#include <unordered_map>
#include <string>

struct identity_hash
{
	size_t operator()(uint64_t value) const noexcept { return value; }
};

class symbol_table
{
public:
	static constexpr uint16_t invalid_index = 0xFFFF;

	uint64_t getHash(const std::string& name) const;

	uint16_t getValue(const std::string& name) const;
	uint16_t getValue(uint64_t hash) const;

	void setValue(uint64_t hash, uint16_t value);

	std::unordered_map<uint64_t, uint16_t, identity_hash> symbol_table;
};
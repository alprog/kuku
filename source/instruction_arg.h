
#pragma once

#include "types.h"
#include "cell.h"

struct instruction_arg_meta_base
{
	virtual size_t get_size() = 0;
	virtual int get_value(byte* ptr) = 0;
	virtual std::string to_string(byte* ptr) = 0;
};

template <typename T>
struct instruction_arg_meta : public instruction_arg_meta_base
{
	static instruction_arg_meta* get_instance()
	{
		static instruction_arg_meta instance;
		return &instance;
	}

	size_t get_size() override
	{
		return sizeof(T);
	}

	int get_value(byte* ptr) override
	{
		return static_cast<int>(*reinterpret_cast<T*>(ptr));
	}

	std::string to_string(byte* ptr) override
	{
		return std::to_string(*reinterpret_cast<T*>(ptr));
	}
};

struct instruction_arg
{
	std::string name;
	instruction_arg_meta_base* meta;
};

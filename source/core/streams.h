#pragma once

#include <string.h>
#include "types.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>

template <typename T>
class input_stream
{
public:
	virtual bool read(T& out_value) = 0;
};

template <typename T>
class output_stream
{
public:
	virtual void write(T value) = 0;
};

template <typename T>
class string_output_stream : public output_stream<T>
{
public:
	std::basic_ostringstream<T> string_stream;

	virtual void write(T value) override
	{
		string_stream.put(value);
	}
};

template <typename T>
class basic_input_stream : public input_stream<T>
{
public:
	std::basic_istream<T>* stream;

	basic_input_stream(std::basic_istream<T>* stream)
		: stream{ stream }
	{
	}

	~basic_input_stream()
	{
		delete stream;
	}

	virtual bool read(T& out_value) override
	{
		stream->get(out_value);
		return !stream->fail();
	}
};

template <typename T>
class queue_stream : public input_stream<T>, public output_stream<T>
{
public:
	virtual bool read(T& out_value) override
	{
		if (!queue.empty())
		{
			out_value = queue.front();
			queue.pop();
			return true;
		}
		return false;
	}

	virtual void write(T value) override
	{
		queue.push(value);
	}

private:
	std::queue<T> queue;
};
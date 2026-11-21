#pragma once

#include <vector>

template <typename element>
struct stack_ex
{
public:
	template <typename... Args>
	void push_emplace(Args... args)
	{
		elements.emplace_back(args...);
		top_ptr = &top();
	}

	void pop()
	{
		elements.pop_back();
		top_ptr = &top();
	}

	element& top()
	{
		return elements[elements.size() - 1];
	}

	element& level(int level)
	{
		return elements[elements.size() - 1 - level];
	}

	element* top_ptr = nullptr;
	std::vector<element> elements;
};
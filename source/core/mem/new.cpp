
#include <memory>
#include "tracker.h"
#include <map>

auto& get_map()
{
	static std::map<void*, std::size_t> sizes;
	return sizes;
}

void* operator new(std::size_t size) noexcept
{
	auto pointer = malloc(size);
	mem::tracker::instance.allocate(size);
	return pointer;
}

void* operator new[](std::size_t size) noexcept
{
	auto pointer = malloc(size);
	get_map()[pointer] = size;
	mem::tracker::instance.allocate(size);
	return pointer;
}

void operator delete(void* pointer, std::size_t size) noexcept
{
	free(pointer);
	mem::tracker::instance.deallocate(size);
}

void operator delete[](void* pointer) noexcept
{
	free(pointer);
	auto iterator = get_map().find(pointer);
	mem::tracker::instance.deallocate(iterator->second);
	get_map().erase(iterator);
}
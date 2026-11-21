
#pragma once

#include <memory>

template<typename T>
class castable_unique_ptr : public std::unique_ptr<T>
{
public:
	using std::unique_ptr<T>::unique_ptr;
	using std::unique_ptr<T>::operator=;

	operator T* () const { return this->get(); };
};
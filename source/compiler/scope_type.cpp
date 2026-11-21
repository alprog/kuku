
#include "scope_type.h"

scope_type operator|(scope_type lhs, scope_type rhs)
{
	return static_cast<scope_type>(static_cast<int>(lhs) | static_cast<int>(rhs));
}

scope_type operator&(scope_type lhs, scope_type rhs)
{
	return static_cast<scope_type>(static_cast<int>(lhs) & static_cast<int>(rhs));
}

#pragma once

enum class scope_type
{
	none = 0,
	module_root = 1 << 0,
	class_body = 1 << 1,
	function_body = 1 << 2,
	property_body = 1 << 3,
	block_body = 1 << 4,
	loop_body = 1 << 5,

	imperative_scopes = function_body | property_body | block_body | loop_body,
	end_scopes = imperative_scopes | class_body,
	any = end_scopes | module_root
};

scope_type operator|(scope_type lhs, scope_type rhs);
scope_type operator&(scope_type lhs, scope_type rhs);

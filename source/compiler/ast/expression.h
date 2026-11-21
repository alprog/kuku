
#pragma once

class compiler;

namespace stmt
{
	class statement;
}

namespace ast
{
	class expression
	{
	public:
		virtual ~expression() = default;

		virtual void compile(compiler& compiler) = 0;

		virtual void semantic_analyze(stmt::statement& statement) {}
	};
}

#pragma once

namespace mem
{
	class tracker
	{
	public:
		static tracker instance;

		~tracker();

		static void print_diagnostics();

		void allocate(int size);
		void deallocate(int size);

		int count = 0;
		int total_size = 0;
		bool enabled = true;
	};
}
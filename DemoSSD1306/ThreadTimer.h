#pragma once

#include <chrono>

using namespace std;
using std::chrono::steady_clock;

class ThreadTimer
{
	public:

		ThreadTimer(std::function<void(time_t)> func, unsigned int interval);
		~ThreadTimer();

	private:

		static time_t steady_clock_to_time_t(steady_clock::time_point t);
		std::thread innerThread;
		bool enabled = true;
};


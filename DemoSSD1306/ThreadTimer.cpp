#include <thread>

#include "ThreadTimer.h"

using namespace std;
using std::chrono::steady_clock;
using std::chrono::system_clock;

ThreadTimer::ThreadTimer(std::function<void(time_t)> func, unsigned int interval)
{
	innerThread = std::thread([func, interval, this]()
	{
		while (enabled)
		{
			this->InvokeCounter++;

			auto time_point = std::chrono::steady_clock::now();
			std::time_t now_c = steady_clock_to_time_t(time_point);

			auto x = time_point + std::chrono::milliseconds(interval);
			func(now_c);
			std::this_thread::sleep_until(x);
		}
	});
	innerThread.detach();
}


ThreadTimer::~ThreadTimer()
{
	enabled = false;
	innerThread.join();
}

time_t ThreadTimer::steady_clock_to_time_t(steady_clock::time_point t)
{
	return system_clock::to_time_t(system_clock::now()
		+ (t - steady_clock::now()));
}
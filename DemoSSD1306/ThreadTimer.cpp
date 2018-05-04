#include <thread>

#include "ThreadTimer.h"

using namespace std;
using std::chrono::steady_clock;
using std::chrono::system_clock;

ThreadTimer::ThreadTimer(std::function<void(time_t)> func, unsigned int interval)
{
	_func = func;
	_interval = interval;

}


ThreadTimer::~ThreadTimer()
{
	enabled = false;
	_innerThread.join();
}

void ThreadTimer::Start()
{
	_innerThread = std::thread([this]()
	{
		while (enabled)
		{
			auto time_point = std::chrono::steady_clock::now();
			std::time_t now_c = steady_clock_to_time_t(time_point);

			auto x = time_point + std::chrono::milliseconds(this->_interval);
			this->_func(now_c);
			std::this_thread::sleep_until(x);
		}
	});
	this->_innerThread.detach();
}



time_t ThreadTimer::steady_clock_to_time_t(steady_clock::time_point t)
{
	return system_clock::to_time_t(system_clock::now()
		+ (t - steady_clock::now()));
}
#pragma once
#include "BaseSignaller.h"

#include <chrono>

using namespace std;
using std::chrono::steady_clock;

class TimerSignaller : BaseSignaller
{
	public:

		TimerSignaller(std::function<void(time_t)> func, unsigned int interval);
		~TimerSignaller();

		void Start();

	private:

		static time_t steady_clock_to_time_t(steady_clock::time_point t);
		std::thread _innerThread;
		std::function<void(time_t)> _func;
		unsigned int _interval;
		bool enabled = true;
};


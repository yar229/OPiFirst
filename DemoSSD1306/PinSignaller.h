#pragma once

#include <functional>

using namespace std;

class PinSignaller
{
	public:

		PinSignaller(int pin, int mode, std::function<void(void)> callback);
		~PinSignaller();

		void Start();

		int SignalCounter = 0;

	private:

		void CallbackWrapper();

		int _pin;
		int _mode;
		std::function<void(void)> _callback;

};


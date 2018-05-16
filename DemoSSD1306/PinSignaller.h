#pragma once

#include <functional>

using namespace std;

class PinSignaller
{
	public:

		PinSignaller(int pin, int mode, std::function<void(int, int)> callback);
		~PinSignaller();

		void Start();

	private:

		void CallbackWrapper();

		int _pin;
		int _mode;
		std::function<void(int, int)> _callback;

};



#include "PinSignaller.h"

#include <stdio.h>
#include <functional>

#include "callbackMethod.h"

#ifdef __cplusplus
extern "C"
{
#endif
	#include <wiringPi.h>
#ifdef __cplusplus
}
#endif


PinSignaller::PinSignaller(int pin, int mode, std::function<void(int, int)> callback)
{
	_pin = pin;
	_mode = mode;
	_callback = callback;
}


PinSignaller::~PinSignaller()
{
}

typedef void(*callback_t)();

void PinSignaller::Start()
{
	//pinMode(_pin, INPUT);

	Callback<void()>::func = std::bind(&PinSignaller::CallbackWrapper, this);
	callback_t func = static_cast<callback_t>(Callback<void()>::callback);

	//try resistors...
	if (_mode && INT_EDGE_FALLING)
		pullUpDnControl(_pin, PUD_DOWN);
	else if (_mode && INT_EDGE_RISING)
		pullUpDnControl(_pin, PUD_UP);

	wiringPiISR(_pin, _mode, func);
}

void PinSignaller::CallbackWrapper()
{
	int pinState = digitalRead(_pin);
	if (
			(_mode && INT_EDGE_RISING && pinState == HIGH) ||
			(_mode && INT_EDGE_FALLING && pinState == LOW)
		)
	{
		_callback(_pin, pinState);
	}

}

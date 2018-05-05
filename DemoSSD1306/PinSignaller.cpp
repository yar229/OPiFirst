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


PinSignaller::PinSignaller(int pin, int mode, std::function<void(void)> callback)
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
	Callback<void()>::func = std::bind(&PinSignaller::CallbackWrapper, this);
	callback_t func = static_cast<callback_t>(Callback<void()>::callback);

	wiringPiISR(_pin, _mode, func);
}

void PinSignaller::CallbackWrapper()
{
	SignalCounter++;
	_callback();
}

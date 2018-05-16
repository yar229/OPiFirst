#include "RotatorSignaller.h"

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


RotatorSignaller::RotatorSignaller(int pinLeft, int pinRight, std::function<void(int)> callback)
{
	_pinLeft = pinLeft;
	_pinRight = pinRight;
	_callback = callback;

	_sigLeft = new PinSignaller(_pinLeft, INT_EDGE_BOTH, [=](int pin, int buttonState)
	{
		_isPinLeftPressed = buttonState;
		if (_isPinLeftPressed && _isPinRightPressed)
			_callback(-1); // callback(left);
	});
	_sigRight = new PinSignaller(_pinLeft, INT_EDGE_BOTH, [=](int pin, int buttonState)
	{
		_isPinRightPressed = buttonState;
		if (_isPinLeftPressed && _isPinRightPressed)
			_callback(1); // callback(right);
	});
}

RotatorSignaller::~RotatorSignaller()
{
	delete _sigLeft;
	delete _sigRight;
}

void RotatorSignaller::Start()
{
	_sigLeft->Start();
	_sigRight->Start();
}



#pragma once
#include <functional>
#include "PinSignaller.h"

class RotatorSignaller
{
public:
	RotatorSignaller(int pinLeft, int pinRight, std::function<void(int)> callback);
	~RotatorSignaller();

	void Start();
	

private:

	int _pinLeft;
	int _pinRight;

	PinSignaller* _sigLeft;
	PinSignaller* _sigRight;

	bool _isPinLeftPressed = false;
	bool _isPinRightPressed = false;

	std::function<void(int)> _callback;
};


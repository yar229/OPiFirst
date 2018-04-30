#include <iostream>
#include <stdexcept>

#include <cstdio>
#include <csignal>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <wiringPi.h>



#define PIN_LED 1	// gpio readall ; wPi = 1, Name = GPIO.1, Phys = 12
#define ESPERA 1000 // 1s


void signalHandler(int signum)
{
	digitalWrite(PIN_LED, LOW);
	printf(" = Cancelled.");
	exit(signum);
}

int main(void)
{
	signal(SIGINT, signalHandler);

	if (wiringPiSetup() < 0)
	{
		fprintf(stderr, "Unable to setup wiringPi: %s\n", strerror(errno));
		return 1;
	}
	pinMode(PIN_LED, OUTPUT);

	try
	{
		while (true)
		{
			digitalWrite(PIN_LED, HIGH);
			delay(ESPERA);
			digitalWrite(PIN_LED, LOW);
			delay(ESPERA);
			
			//throw std::invalid_argument("received negative value");
		}
	}
	catch (const std::invalid_argument& e) 
	{
		int i = 1;
		// do stuff with exception... 
	}
	catch (const int & e) 
	{
		//cout << "string caught main" << endl;
	}
	catch (int i) 
	{
		//cout << "int caught main" << endl;
	}

	return 0;
}


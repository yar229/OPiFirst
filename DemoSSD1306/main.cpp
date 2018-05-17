#include <thread>
#include <chrono>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif
	#include <wiringPi.h>
	#include "ssd1306_i2c.h"

	#include "TimerSignaller.h"
	#include "PinSignaller.h"
	
	#include "OledDisplay.h"
	#include "VolumePainter.h"	
	#include "DateTimePainter.h"	
	#include "StartPainter.h"
	#include "WifiPainter.h"
#ifdef __cplusplus
}
#endif


int main1()
{
	if (wiringPiSetup() < 0) 
	{
		fprintf(stderr, "Unable to setup wiringPi: %s\n", errno);
		return 1;
	}

	//ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	//ssd1306_clearDisplay();

	OledDisplay* display = new OledDisplay();
	display->UpsideDown(true);

	//=== draw start image ===================================================================================

	auto startPainter = new StartPainter(display);
	startPainter->Draw();
	display->Display();
	display->ClearDisplay();
	std::this_thread::sleep_for(std::chrono::seconds(3));
	delete startPainter;

	//=== draw date/time/WiFi on timer =======================================================================

	DateTimePainter* dateTimePainter = new DateTimePainter(display);
	volatile int dateTimeInvokeCounter = 0;
	WifiPainter* wifiPainter = new WifiPainter(display);
	TimerSignaller* timeSignaller = new TimerSignaller([display, dateTimePainter, wifiPainter, &dateTimeInvokeCounter](time_t t)
	{
		//clock_t start = clock();

		dateTimePainter->Draw(t);
		
		if (dateTimeInvokeCounter++ % 5 == 0)
			wifiPainter->Draw();

		display->Display();

		//clock_t stop = clock();
		//double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
		//printf("Time elapsed in ms: %f", elapsed);
	}, 1000);
	timeSignaller->Start();
	//========================================================================================================

	//=== button pressed =====================================================================================

	volatile int signalCounter = 0;
	VolumePainter* volumePainter = new VolumePainter(display);
	PinSignaller* pinSignaller = new PinSignaller(7, INT_EDGE_FALLING, [display, volumePainter, &signalCounter](int pin, int buttonState)
	{
		volumePainter->Draw(signalCounter++);
		display->Display();
	});
	pinSignaller->Start();
	//========================================================================================================

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	delete timeSignaller;
	delete dateTimePainter;
}
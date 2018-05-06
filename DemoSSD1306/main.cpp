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
	
	#include "VolumePainter.h"	
	#include "DateTimePainter.h"	
	#include "StartPainter.h"
	#include "WifiPainter.h"
#ifdef __cplusplus
}
#endif

void myInterrupt7(void) 
{

	//pinMode(7, INPUT);
}

int main()
{
	if (wiringPiSetup() < 0) 
	{
		fprintf(stderr, "Unable to setup wiringPi: %s\n", errno);
		return 1;
	}
	////pinMode(7, INPUT);
	//if (wiringPiISR(7, INT_EDGE_FALLING, &myInterrupt7) < 0)
	//{
	//	fprintf(stderr, "Unable to setup ISR: %s\n", errno);
	//	return 1;
	//}

	//while (true)
	//{
	//	std::this_thread::sleep_for(std::chrono::seconds(5));
	//}

	//return 0;


	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	ssd1306_clearDisplay();

	//=== draw start image ===================================================================================
	auto startPainter = new StartPainter();
	startPainter->Draw();
	ssd1306_display();
	ssd1306_clearDisplay();
	std::this_thread::sleep_for(std::chrono::seconds(3));
	delete startPainter;

	//=== draw date/time/WiFi on timer =======================================================================
	DateTimePainter* dateTimePainter = new DateTimePainter();
	int dateTimeInvokeCounter = 0;
	WifiPainter* wifiPainter = new WifiPainter();
	TimerSignaller* dateTimeTimer = new TimerSignaller([&dateTimeInvokeCounter, dateTimePainter, wifiPainter](time_t t)
	{
		//clock_t start = clock();

		dateTimePainter->Draw(t);
		
		if (dateTimeInvokeCounter++ % 5 == 0)
			wifiPainter->Draw();

		ssd1306_display();

		//clock_t stop = clock();
		//double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
		//printf("Time elapsed in ms: %f", elapsed);
	}, 1000);
	dateTimeTimer->Start();
	//========================================================================================================

	//=== button pressed =====================================================================================
	int signalCounter = 0;
	int *pSignalcounter = &signalCounter;
	VolumePainter* volumePainter = new VolumePainter();
	PinSignaller* pinSignaller = new PinSignaller(7, INT_EDGE_FALLING, [volumePainter, pSignalcounter]()
	{
		volumePainter->Draw((*pSignalcounter)++);
	});
	pinSignaller->Start();

	//wiringPiISR(7, INT_EDGE_FALLING, &myInterrupt7);
	//========================================================================================================

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	delete dateTimeTimer;
	delete dateTimePainter;
}
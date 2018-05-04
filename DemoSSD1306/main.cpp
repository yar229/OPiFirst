#include <thread>
#include <chrono>
#include <time.h>
#include "ThreadTimer.h"

#ifdef __cplusplus
extern "C"
{
#endif
	#include "ssd1306_i2c.h"
	#include "DateTimePainter.h"	
	#include "StartPainter.h"
	#include "WifiPainter.h"
#ifdef __cplusplus
}
#endif

int main()
{
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
	ThreadTimer* dateTimeTimer = new ThreadTimer([&dateTimeInvokeCounter, dateTimePainter, wifiPainter](time_t t)
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

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	delete dateTimeTimer;
	delete dateTimePainter;
}
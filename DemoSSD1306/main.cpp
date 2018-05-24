#include <thread>
#include <chrono>
#include <time.h>

#ifdef __cplusplus
extern "C"
{
#endif
	#include "callbackMethod.h"

	#include "lvgl/lv_core/lv_refr.h"

	#include "LvglScreen.h"

	//#include <wiringPi.h>
	//#include "ssd1306_i2c.h"

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

using namespace std;
using std::chrono::steady_clock;
using std::chrono::system_clock;

time_t steady_clock_to_time_t(steady_clock::time_point t)
{
	return system_clock::to_time_t(system_clock::now()
		+ (t - steady_clock::now()));
}

int main()
{
	LvglScreen* screen = new LvglScreen();

	DateTimePainter* dateTimePainter = new DateTimePainter(screen);
	//volatile int dateTimeInvokeCounter = 0;
	////WifiPainter* wifiPainter = new WifiPainter(display);
	//TimerSignaller* timeSignaller = new TimerSignaller([dateTimePainter, /*wifiPainter,*/ &dateTimeInvokeCounter](time_t t)
	//{
	//	//clock_t start = clock();

	//	dateTimePainter->Draw(t);
	//	//lv_tick_inc(5);
	//	//lv_task_handler();
	//		

	//	//lv_task_create()

	//	//if (dateTimeInvokeCounter++ % 5 == 0)
	//	//	wifiPainter->Draw();

	//	/*display->Display();*/

	//	//clock_t stop = clock();
	//	//double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	//	//printf("Time elapsed in ms: %f", elapsed);
	//}, 1000);
	//timeSignaller->Start();
	auto fn = fnptr<void(void*)>([dateTimePainter] 
	{
		std::time_t now_c = steady_clock_to_time_t(std::chrono::steady_clock::now());
		dateTimePainter->Draw(now_c);
	});
	lv_task_create(fn, 1000, LV_TASK_PRIO_MID, NULL);

	//lv_task_init();
	while (true)
	{
		lv_tick_inc(5);
		lv_task_handler();
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	//delete timeSignaller;
	delete dateTimePainter;


	/* OLD 
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

	//DateTimePainter* dateTimePainter = new DateTimePainter(display);
	//volatile int dateTimeInvokeCounter = 0;
	//WifiPainter* wifiPainter = new WifiPainter(display);
	//TimerSignaller* timeSignaller = new TimerSignaller([display, dateTimePainter, wifiPainter, &dateTimeInvokeCounter](time_t t)
	//{
	//	//clock_t start = clock();

	//	dateTimePainter->Draw(t);
	//	
	//	if (dateTimeInvokeCounter++ % 5 == 0)
	//		wifiPainter->Draw();

	//	display->Display();

	//	//clock_t stop = clock();
	//	//double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
	//	//printf("Time elapsed in ms: %f", elapsed);
	//}, 1000);
	//timeSignaller->Start();
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
	*/
}
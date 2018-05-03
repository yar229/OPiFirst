#include <thread>
#include <chrono>
#include <time.h>
#include "ThreadTimer.h"

#ifdef __cplusplus
extern "C"
{
#endif
	#include "ssd1306_i2c.h"
	#include "DrawDatetime.h"	
#ifdef __cplusplus
}
#endif



int main()
{
	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	//ssd1306_invertDisplay(1);
	//ssd1306_rotation(2);
	ssd1306_upsideDown(1);
	ssd1306_clearDisplay();

	auto dateTimePainter = new DateTimePainter();
	auto timer = new ThreadTimer([=](time_t t) { dateTimePainter->PrintDatetime(t); }, 1000);

	while (true)
	{
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}

	delete timer;
	delete dateTimePainter;
}
#include <iostream>
#include <thread>
#include <chrono>

#ifdef __cplusplus
extern "C"
{
#endif
#include "ssd1306_i2c.h"
#include "fonts.h"
#include "DrawDatetime.h"
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

void timer_start(std::function<void(time_t)> func, unsigned int interval)
{
	std::thread([func, interval]()
	{
		while (true)
		{
			auto time_point = std::chrono::steady_clock::now();
			std::time_t now_c = steady_clock_to_time_t(time_point);

			auto x = time_point + std::chrono::milliseconds(interval);
			func(now_c);
			std::this_thread::sleep_until(x);
		}
	}).detach();
}

char datebuffer[100];
char timebuffer[26];
char secbuffer[4];

font_info_t* smallFont = (font_info_t *)(fonts[2]);
font_info_t* bigFont = (font_info_t *)(fonts[4]);

void PrintDatetime(std::time_t time)
{
	//ssd1306_drawPixel(5, 5, WHITE);

	auto local = localtime(&time);

	strftime(datebuffer, 100, "%a, %Y-%m-%d", local);
	strftime(timebuffer, 26, "%H:%M", local);
	strftime(secbuffer, 4, "%S", local);

	ssd1306_clearDisplay();

	ssd1306_drawString(smallFont, (unsigned char *)datebuffer, 27, 5);
	ssd1306_drawString(bigFont, (unsigned char *)timebuffer, 30, 15);
	ssd1306_drawString(smallFont, (unsigned char *)secbuffer, 110, 15);

	ssd1306_display();
}

#include <iostream>
#include <chrono>
#include <cstring>

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

void DateTimePainter::PrintDatetime(std::time_t time)
{
	// till there will be correct symbol width printing
	//ssd1306_clearDisplay();
	//_doFullRedraw = true;

	auto local = localtime(&time);

	if (_doFullRedraw) ssd1306_clearDisplay();

	if (_doFullRedraw || _oldTime->tm_year != local->tm_year || _oldTime->tm_mon != local->tm_mon || _oldTime->tm_mday != local->tm_mday)
	{	// draw year-month-day line
		strftime(_printBuffer, 100, "%a, %Y-%m-%d", local);
		ssd1306_drawString(
			_fontSmall, 
			(unsigned char *)_printBuffer, 
			SSD1306_LCDWIDTH / 2 - ssd1306_stringWidth(_fontSmall, (unsigned char *)_printBuffer) / 2,
			_coordYDate);
	}

	if (_doFullRedraw || _oldTime->tm_hour != local->tm_hour)
		DrawNum2(_fontBig, local->tm_hour, _coordXHour, _coordYTime, _printBuffer);

	if (_doFullRedraw || 0 == _oldTime->tm_year)
		ssd1306_drawString(_fontBig, (unsigned char *)":", _coordXColon, _coordYTime);

	if (_doFullRedraw || _oldTime->tm_min != local->tm_min)
		DrawNum2(_fontBig, local->tm_min, _coordXMinute, _coordYTime, _printBuffer);

	if (_doFullRedraw || _oldTime->tm_sec != local->tm_sec)
		DrawNum2(_fontSmall, local->tm_sec, _coordXSecond, _coordYTime, _printBuffer);

	ssd1306_display();

	memcpy(_oldTime, local, sizeof(struct tm));
}

inline void DateTimePainter::DrawNum2(font_info_t* font, int value, int x, int y, char *buffer)
{
	sprintf(buffer, "%02d", value);
	ssd1306_drawString(font, (unsigned char *)buffer, x, y);
}


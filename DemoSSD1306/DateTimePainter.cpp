#include <iostream>
#include <chrono>
#include <cstring>

#ifdef __cplusplus
extern "C"
{
#endif
	#include "fonts.h"
	#include "DateTimePainter.h"
#ifdef __cplusplus
}
#endif

using namespace std;
using std::chrono::steady_clock;
using std::chrono::system_clock;

DateTimePainter::DateTimePainter(OledDisplay *display)
{
	_display = display;
}

DateTimePainter::~DateTimePainter()
{
}

void DateTimePainter::Draw(std::time_t time)
{
	auto local = localtime(&time);

	if (_doFullRedraw) _display->ClearDisplay();

	if (_firstDraw || _doFullRedraw || _oldTime->tm_year != local->tm_year || _oldTime->tm_mon != local->tm_mon || _oldTime->tm_mday != local->tm_mday)
	{	// draw year-month-day line
		_display->FillRectangle(0, _coordYDate, _display->Width, _fontSmall->height, BLACK); //dirty clean date string

		strftime(_printBuffer, 100, "%a, %Y-%m-%d", local);
		_display->DrawString(
			_fontSmall, 
			(unsigned char *)_printBuffer, 
			_display->Width / 2 - ssd1306_stringWidth(_fontSmall, (unsigned char *)_printBuffer) / 2,
			_coordYDate);
	}

	if (_firstDraw || _doFullRedraw || _oldTime->tm_hour != local->tm_hour)
	{
		_display->FillRectangle(_coordXHour, _coordYTime, _coordXColon - _coordXHour, _fontBig->height, BLACK); //dirty clean time left part (hours)
		DrawNum2(_fontBig, local->tm_hour, _coordXHour, _coordYTime, _printBuffer);
	}

	if (_firstDraw || _firstDraw || _doFullRedraw || 0 == _oldTime->tm_year)
		_display->DrawString(_fontBig, (unsigned char *)":", _coordXColon, _coordYTime);

	if (_firstDraw || _doFullRedraw || _oldTime->tm_min != local->tm_min)
	{
		_display->FillRectangle(_coordXMinute, _coordYTime, _coordXSecond - _coordXMinute, _fontBig->height, BLACK); //dirty clean time right part (mins and secs)
		DrawNum2(_fontBig, local->tm_min, _coordXMinute, _coordYTime, _printBuffer);
	}

	if (_firstDraw || _doFullRedraw || _oldTime->tm_sec != local->tm_sec)
	{
		_display->FillRectangle(_coordXSecond, _coordYTime, _display->Width - _coordXSecond, _fontSmall->height, BLACK); //dirty clean time right part (mins and secs)
		DrawNum2(_fontSmall, local->tm_sec, _coordXSecond, _coordYTime, _printBuffer);
	}

	memcpy(_oldTime, local, sizeof(struct tm));

	if (_firstDraw) _firstDraw = false;
}

inline void DateTimePainter::DrawNum2(font_info_t* font, int value, int x, int y, char *buffer)
{
	sprintf(buffer, "%02d", value);
	_display->DrawString(font, (unsigned char *)buffer, x, y);
}


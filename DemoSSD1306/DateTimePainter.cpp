#include <iostream>
#include <chrono>
#include <cstring>

#ifdef __cplusplus
extern "C"
{
#endif
	#include "DateTimePainter.h"
	#include "LvglScreen.h"
#ifdef __cplusplus
}
#endif

using namespace std;
using std::chrono::steady_clock;
using std::chrono::system_clock;

DateTimePainter::DateTimePainter(LvglScreen * screen)
{
	_screen = screen;

	_boxMain = lv_cont_create(lv_scr_act(), NULL);
	lv_obj_set_style(_boxMain, &lv_style_pretty);
	lv_cont_set_fit(_boxMain, true, true);

	_lblDate = lv_label_create(_boxMain, NULL);
	lv_obj_align(_lblDate, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);
	lv_label_set_text(_lblDate, "Mon, 01 Jan 1970");

	_lblTime = lv_label_create(_boxMain, NULL);
	lv_obj_align(_lblTime, NULL, LV_ALIGN_IN_TOP_MID, 0, 40);
	lv_label_set_text(_lblTime, "21:45");

	_lblSeconds = lv_label_create(_boxMain, NULL);
	lv_label_set_text(_lblSeconds, "56");

	lv_obj_align(_boxMain, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);
}

DateTimePainter::~DateTimePainter()
{
}

void DateTimePainter::Draw(std::time_t time)
{
	auto local = localtime(&time);

	if (_firstDraw || _oldTime->tm_year != local->tm_year || _oldTime->tm_mon != local->tm_mon || _oldTime->tm_mday != local->tm_mday)
	{	// draw year-month-day line
		strftime(_printBuffer, 100, "%a, %Y-%m-%d", local);
		lv_label_set_text(_lblDate, _printBuffer);
	}

	if (_firstDraw || _oldTime->tm_hour != local->tm_hour || _oldTime->tm_min != local->tm_min)
	{
		strftime(_printBuffer, 100, "%HH:%MM", local);
		lv_label_set_text(_lblTime, _printBuffer);
	}

	if (_firstDraw || _oldTime->tm_sec != local->tm_sec)
	{
		sprintf(_printBuffer, "%02d", local->tm_sec);
		lv_label_set_text(_lblSeconds, _printBuffer);
	}

	memcpy(_oldTime, local, sizeof(struct tm));

	if (_firstDraw) _firstDraw = false;
}



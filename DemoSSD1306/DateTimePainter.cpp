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

#define USE_LV_FONT_DEJAVU_10 1

using namespace std;
using std::chrono::steady_clock;
using std::chrono::system_clock;

DateTimePainter::DateTimePainter(LvglScreen * screen)
{
	_screen = screen;

	// style
	lv_style_copy(&_styleCommon, &lv_style_plain);    /*Copy a built-in style to initialize the new style*/
	_styleCommon.body.main_color = LV_COLOR_BLACK;
	_styleCommon.body.grad_color = LV_COLOR_BLACK;
	_styleCommon.body.radius = 10;
	_styleCommon.body.border.color = LV_COLOR_GRAY;
	_styleCommon.body.border.width = 2;
	_styleCommon.body.border.opa = LV_OPA_50;
	_styleCommon.body.padding.hor = 5;            /*Horizontal padding, used by the bar indicator below*/
	_styleCommon.body.padding.ver = 5;            /*Vertical padding, used by the bar indicator below*/
	_styleCommon.text.color = LV_COLOR_WHITE;

	lv_style_copy(&_styleSmallText, &_styleCommon);
	_styleSmallText.text.font = &lv_font_dejavu_20;

	


	_boxMain = lv_cont_create(_screen->Screen, NULL);
	lv_obj_set_style(_boxMain, &_styleCommon);
	lv_cont_set_fit(_boxMain, true, true);

	_lblDate = lv_label_create(_boxMain, NULL);
	lv_obj_set_style(_lblDate, &_styleSmallText);
	lv_label_set_text(_lblDate, "Mon, 01 Jan 1970");
	lv_obj_align(_lblDate, NULL, LV_ALIGN_IN_TOP_MID, 0, 20);

	_lblTime = lv_label_create(_boxMain, NULL);
	lv_obj_set_style(_lblTime, &_styleCommon);
	lv_label_set_text(_lblTime, "21:45");
	lv_obj_align(_lblTime, NULL, LV_ALIGN_IN_TOP_MID, 0, 40);


	_lblSeconds = lv_label_create(_boxMain, NULL);
	lv_obj_set_style(_lblSeconds, &_styleSmallText);
	lv_label_set_text(_lblSeconds, "56");
	lv_obj_align(_lblSeconds, NULL, LV_ALIGN_IN_TOP_MID, 0, 60);

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
		lv_obj_invalidate(_lblDate);
	}

	if (_firstDraw || _oldTime->tm_hour != local->tm_hour || _oldTime->tm_min != local->tm_min)
	{
		strftime(_printBuffer, 100, "%HH:%MM", local);
		lv_label_set_text(_lblTime, _printBuffer);
		lv_obj_invalidate(_lblTime);
	}

	if (_firstDraw || _oldTime->tm_sec != local->tm_sec)
	{
		sprintf(_printBuffer, "%02d", local->tm_sec);
		lv_label_set_text(_lblSeconds, _printBuffer);
		lv_obj_invalidate(_lblSeconds);
	}

	memcpy(_oldTime, local, sizeof(struct tm));

	if (_firstDraw) _firstDraw = false;
}



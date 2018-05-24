#pragma once

#include <chrono>

#ifdef __cplusplus
extern "C"
{
#endif
	#include "lvgl/lvgl.h"
	#include "lv_drivers/display/fbdev.h"

	#include "LvglScreen.h"
#ifdef __cplusplus
}
#endif

class DateTimePainter
{
	public:
		DateTimePainter(LvglScreen* screen);
		~DateTimePainter();

		void Draw(std::time_t time);

	private:
		LvglScreen *_screen;

		lv_style_t _styleCommon;
		lv_style_t _styleSmallText;


		lv_obj_t * _boxMain;
		lv_obj_t * _lblDate;
		lv_obj_t * _lblTime;
		lv_obj_t * _lblSeconds;


		bool _firstDraw = true;

		char _printBuffer[16];
		tm* _oldTime = new tm();
};

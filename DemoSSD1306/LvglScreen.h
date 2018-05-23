#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
	#include "lvgl/lvgl.h"
	#include "lv_drivers/display/fbdev.h"
#ifdef __cplusplus
}
#endif

class LvglScreen
{
public:
	LvglScreen();
	~LvglScreen();

	lv_style_t Style;
private:
	lv_disp_drv_t _disp_drv;
};


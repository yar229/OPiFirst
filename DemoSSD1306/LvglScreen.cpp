#include "LvglScreen.h"

LvglScreen::LvglScreen()
{
	/*LittlevGL init*/
	lv_init();

	/*Linux frame buffer device init*/
	fbdev_init();

	/*Add a display the LittlevGL sing the frame buffer driver*/
	lv_disp_drv_init(&_disp_drv);
	_disp_drv.disp_flush = fbdev_flush;      /*It flushes the internal graphical buffer to the frame buffer*/
	lv_disp_drv_register(&_disp_drv);

	// style
	lv_style_copy(&Style, &lv_style_plain);    /*Copy a built-in style to initialize the new style*/
	Style.body.main_color = LV_COLOR_BLACK;
	Style.body.grad_color = LV_COLOR_BLACK;
	Style.body.radius = 10;
	Style.body.border.color = LV_COLOR_GRAY;
	Style.body.border.width = 2;
	Style.body.border.opa = LV_OPA_50;
	Style.body.padding.hor = 5;            /*Horizontal padding, used by the bar indicator below*/
	Style.body.padding.ver = 5;            /*Vertical padding, used by the bar indicator below*/
	Style.text.color = LV_COLOR_RED;

	Screen = lv_obj_create(NULL, NULL);
	lv_obj_set_style(Screen, &Style);
	lv_scr_load(Screen);
}


LvglScreen::~LvglScreen()
{
}

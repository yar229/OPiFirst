#include "unistd.h"

#ifdef __cplusplus
extern "C"
{
#endif
	#include "lvgl/lvgl.h"
	#include "lv_drivers/display/fbdev.h"
#ifdef __cplusplus
}
#endif

int main(void)
{
	/*LittlevGL init*/
	lv_init();

	/*Linux frame buffer device init*/
	fbdev_init();

	/*Add a display the LittlevGL sing the frame buffer driver*/
	lv_disp_drv_t disp_drv;
	lv_disp_drv_init(&disp_drv);
	disp_drv.disp_flush = fbdev_flush;      /*It flushes the internal graphical buffer to the frame buffer*/
	lv_disp_drv_register(&disp_drv);


	// style
	static lv_style_t style1;
	lv_style_copy(&style1, &lv_style_plain);    /*Copy a built-in style to initialize the new style*/
	style1.body.main_color = LV_COLOR_BLACK;
	style1.body.grad_color = LV_COLOR_BLUE;
	style1.body.radius = 10;
	style1.body.border.color = LV_COLOR_GRAY;
	style1.body.border.width = 2;
	style1.body.border.opa = LV_OPA_50;
	style1.body.padding.hor = 5;            /*Horizontal padding, used by the bar indicator below*/
	style1.body.padding.ver = 5;            /*Vertical padding, used by the bar indicator below*/
	style1.text.color = LV_COLOR_RED;


	/*Create a "Hello world!" label*/
	lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
	lv_obj_set_style(label, &style1);
	lv_label_set_text(label, "Hello world!");
	
	lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

	/*Handle LitlevGL tasks (tickless mode)*/
	while (1) 
	{
		lv_tick_inc(5);
		lv_task_handler();
		usleep(5000);
	}

	return 0;
}
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

	/*Create a "Hello world!" label*/
	lv_obj_t * label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label, "Hello world!");
	lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

	/*Handle LitlevGL tasks (tickless mode)*/
	while (1) {
		lv_tick_inc(5);
		lv_task_handler();
		usleep(5000);
	}

	return 0;
}
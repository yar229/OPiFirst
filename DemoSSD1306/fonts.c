/*
* oled_fonts.c
*
*/
#include "fonts.h"

extern const font_info_t glcd_5x7_font_info;
extern const font_info_t glcdru_5x7_font_info;
extern const font_info_t tahoma_8pt_font_info;
extern const font_info_t segoeUISemibold_24pt_font_info;
extern const font_info_t consolas_24pt_font_info;
extern const font_info_t consolas_11pt_font_info;
extern const font_info_t century_10pt_font_info;
extern const font_info_t century_11pt_font_info;



const font_info_t * fonts[NUM_FONTS] =
{
	&glcd_5x7_font_info,
	&glcdru_5x7_font_info,
	&tahoma_8pt_font_info,
	&segoeUISemibold_24pt_font_info,
	&consolas_24pt_font_info,
	&consolas_11pt_font_info,
	&century_10pt_font_info,
	&century_11pt_font_info,
};
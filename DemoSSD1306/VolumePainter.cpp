#include "VolumePainter.h"
#include <iostream>
#include <cstring>


#ifdef __cplusplus
extern "C"
{
#endif
	#include "ssd1306_i2c.h"
#ifdef __cplusplus
}
#endif

VolumePainter::VolumePainter(OledDisplay *display)
{
	_display = display;
}


VolumePainter::~VolumePainter()
{
}


void VolumePainter::Draw(int num)
{
	sprintf(_printBuffer, "%02d", num);
	_display->DrawString(_fontBig, (unsigned char *)_printBuffer, 0, 0);
}

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

VolumePainter::VolumePainter()
{
}


VolumePainter::~VolumePainter()
{
}


void VolumePainter::Draw(int num)
{
	sprintf(_printBuffer, "%02d", num);

	ssd1306_clearDisplay();

	ssd1306_drawString(_fontBig, (unsigned char *)_printBuffer, 0, 0);
}

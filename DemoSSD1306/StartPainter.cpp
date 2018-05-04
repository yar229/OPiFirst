#include "StartPainter.h"



StartPainter::StartPainter()
{
}


StartPainter::~StartPainter()
{
}

void StartPainter::Draw()
{
	//ssd1306_copyBuffer((int *)_buffer, SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8);
	ssd1306_drawBitmap(0, 0, _buffer, SSD1306_LCDWIDTH, SSD1306_LCDHEIGHT, WHITE, BLACK);
}

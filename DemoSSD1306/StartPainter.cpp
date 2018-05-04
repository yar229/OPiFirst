#include "StartPainter.h"



StartPainter::StartPainter()
{
}


StartPainter::~StartPainter()
{
}

void StartPainter::Draw()
{
	ssd1306_drawBuffer((int *)_buffer, sizeof(_buffer));
	ssd1306_display();
}

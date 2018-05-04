#include "StartPainter.h"



StartPainter::StartPainter()
{
}


StartPainter::~StartPainter()
{
}

void StartPainter::Draw()
{
	ssd1306_copyBuffer((int *)_buffer, sizeof(_buffer));
}

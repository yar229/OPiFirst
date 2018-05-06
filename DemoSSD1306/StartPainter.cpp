#include "StartPainter.h"



StartPainter::StartPainter(OledDisplay *display)
{
	_display = display;
}


StartPainter::~StartPainter()
{
}

void StartPainter::Draw()
{
	_display->DrawBitmap(0, 0, _buffer, _display->Width, _display->Height, WHITE, BLACK);
}

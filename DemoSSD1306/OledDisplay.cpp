#include "OledDisplay.h"

#include <mutex>
#include <thread>

OledDisplay::OledDisplay()
{
	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	ssd1306_clearDisplay();
}


OledDisplay::~OledDisplay()
{
}

void OledDisplay::UpsideDown(bool yesno)
{
	ssd1306_upsideDown(yesno ? 1 : 0);
}


std::mutex _displayLock;

void OledDisplay::Display()
{
	_displayLock.lock();

	ssd1306_display();

	_displayLock.unlock();
}

void OledDisplay::ClearDisplay()
{
	ssd1306_clearDisplay();
}

void OledDisplay::FillRectangle(int x, int y, int w, int h, int fillColor)
{
	ssd1306_fillRect(x, y, w, h, fillColor);
}

void OledDisplay::DrawString(font_info_t *font, unsigned char *str, int x, int y)
{
	ssd1306_drawString(font, str, x, y);
}

void OledDisplay::DrawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint8_t foreColor, uint8_t backColor)
{
	ssd1306_drawBitmap(x, y, bitmap, w, h, foreColor, backColor);
}


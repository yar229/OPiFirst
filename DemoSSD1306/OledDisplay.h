#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
	#include "ssd1306_i2c.h"
#ifdef __cplusplus
}
#endif



#define BLACK 0
#define WHITE 1
#define INVERSE 2

class OledDisplay
{
	public:
		OledDisplay();
		~OledDisplay();

		void UpsideDown(bool yesno);

		void Display();

		void ClearDisplay();

		void FillRectangle(int x, int y, int w, int h, int fillColor);

		void DrawString(font_info_t * font, unsigned char * str, int x, int y);

		void DrawBitmap(int16_t x, int16_t y, const uint8_t * bitmap, int16_t w, int16_t h, uint8_t foreColor, uint8_t backColor);



		int Width = SSD1306_LCDWIDTH;
		int Height = SSD1306_LCDHEIGHT;


	private:
		//std::mutex _displayLock;
		
};

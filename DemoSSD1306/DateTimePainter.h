#pragma once

#include <chrono>

class DateTimePainter
{
	public:

		void Draw(std::time_t time);

	private:

		inline void DrawNum2(font_info_t* font, int value, int x, int y, char *buffer);

		bool _doFullRedraw;

		char _printBuffer[16];
		tm* _oldTime = new tm();

		font_info_t* _fontSmall = (font_info_t *)(fonts[7]); //[2]);
		font_info_t* _fontBig = (font_info_t *)(fonts[4]);

		//symbol positions for monowidth font
		//const uint8_t _coordXDate = 17;
		const uint8_t _coordYDate = 5;

		const uint8_t _widthCharBig = ssd1306_charWidth(_fontBig, '0');
		const uint8_t _widthCharBigColon = ssd1306_charWidth(_fontBig, ':');

		const uint8_t _coordXHour = SSD1306_LCDWIDTH / 2 - _fontBig->c - 2 * _widthCharBig - _widthCharBigColon / 2;
		const uint8_t _coordXColon = SSD1306_LCDWIDTH / 2 - _widthCharBigColon / 2;
		const uint8_t _coordXMinute = SSD1306_LCDWIDTH / 2 + _widthCharBigColon / 2 + _fontBig->c;
		const uint8_t _coordXSecond = SSD1306_LCDWIDTH / 2 + 3 * _fontBig->c + 2 * _widthCharBig + _widthCharBigColon / 2;
		const uint8_t _coordYTime = 25;
		
};

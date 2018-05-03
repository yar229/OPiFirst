#pragma once

#include <chrono>

class DateTimePainter
{
	public:

		void PrintDatetime(std::time_t time);

	private:

		inline void DrawNum2(font_info_t* font, int value, int x, int y, char *buffer);

		bool _doFullRedraw;

		char _printBuffer[16];
		tm* _oldTime = new tm();

		font_info_t* _fontSmall = (font_info_t *)(fonts[2]);
		font_info_t* _fontBig = (font_info_t *)(fonts[4]);

		//symbol positions for monowidth font
		const uint8_t _coordXDate = 27;
		const uint8_t _coordYDate = 5;

		const uint8_t _coordXHour = SSD1306_LCDWIDTH / 2 - 2 * _fontBig->c - 2 * _fontBig->char_descriptors->width - _fontBig->char_descriptors->width / 2;
		const uint8_t _coordXColon = SSD1306_LCDWIDTH / 2 - _fontBig->char_descriptors->width / 2;
		const uint8_t _coordXMinute = SSD1306_LCDWIDTH / 2 + _fontBig->char_descriptors->width / 2;
		const uint8_t _coordXSecond = SSD1306_LCDWIDTH / 2 + 3 * _fontBig->c + 2 * _fontBig->char_descriptors->width + _fontBig->char_descriptors->width / 2;
		const uint8_t _coordYTime = 15;
		
};

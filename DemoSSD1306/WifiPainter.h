#pragma once

#include <string>
#include "fonts.h"
#include "OledDisplay.h"

using namespace std;

class WifiPainter
{
	public:
		WifiPainter(OledDisplay *display);
		~WifiPainter();
		
		void Draw();
		

	private:
		OledDisplay * _display;

		const font_info_t* _fontSmall = (font_info_t *)(fonts[7]);
		
		static bool IsInterfaceUp(std::string interface);

		const unsigned char _imageWifi[16 * 16 / 8] = 
		{ 
			0x1F, 0xFF,
			0x03, 0xFF,
			0x00, 0xFF,
			0x00, 0x3F,
			0xE0, 0x1F,
			0xFC, 0x0F,
			0x3E, 0x07,
			0x07, 0x07,
			0x03, 0x83,
			0x01, 0xC3,
			0xC0, 0xE1,
			0xF0, 0x61,
			0x38, 0x60,
			0x18, 0x30,
			0x0C, 0x30,
			0x0C, 0x30
		};


};


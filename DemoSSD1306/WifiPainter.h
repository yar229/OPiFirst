#pragma once

#include <string>
#include "fonts.h"

using namespace std;

class WifiPainter
{
	public:
		WifiPainter();
		~WifiPainter();
		
		void Draw();
		

	private:
		const font_info_t* _fontSmall = (font_info_t *)(fonts[7]);
		static bool IsInterfaceUp(std::string interface);

		const int _imageWifi[16 * 16 / 8] =
		{
			0x01, 0x03, 0x82, 0x80, 0x04, 0x04, 0x08, 0x08, 0x10, 0x30,
			0x60, 0xC0, 0x80, 0x00, 0x00, 0x00, 0xE0, 0xE0, 0x60, 0x00,
			0x01, 0x03, 0x06, 0x0C, 0x30, 0x00, 0x00, 0x00, 0x03, 0x0E,
			0x70, 0xE0
		};
};


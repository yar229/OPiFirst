#include <string>
#include <fstream>
#include <streambuf>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif
#include "ssd1306_i2c.h"
#include "fonts.h"
#include "WifiPainter.h"
#ifdef __cplusplus
}
#endif

WifiPainter::WifiPainter()
{
}


WifiPainter::~WifiPainter()
{
}

void WifiPainter::Draw()
{
	const std::string ifname("wlan0");

	//memset(&_imageWifi, 0xFF, SSD1306_LCDWIDTH * SSD1306_LCDHEIGHT / 8);
	
	if (WifiPainter::IsInterfaceUp(ifname))		//ssd1306_drawString((font_info_t*)_fontSmall, (unsigned char *)(WifiPainter::IsInterfaceUp(ifname) ? "WiFi+" : "WiFi-"), 5, 55);
		//ssd1306_drawBitmap(0, 47, _imageWifi, 30,30, WHITE, BLACK);
		ssd1306_drawBitmap(0, 47, _imageWifi, 16, 16, WHITE, BLACK);
	else
		ssd1306_fillRect(0, 47, 16, 16, BLACK);
}

bool WifiPainter::IsInterfaceUp(std::string ifname)
{
	std::ifstream t("/sys/class/net/wlan0/operstate");
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	return  str.substr(0, 2) == "up";
}
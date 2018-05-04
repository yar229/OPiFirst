#include <string>
#include <fstream>
#include <streambuf>

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
	
	if (WifiPainter::IsInterfaceUp(ifname))		//ssd1306_drawString((font_info_t*)_fontSmall, (unsigned char *)(WifiPainter::IsInterfaceUp(ifname) ? "WiFi+" : "WiFi-"), 5, 55);
		ssd1306_drawBitmap(5, 48, _imageWifi, 16, 16, WHITE);
	else
		ssd1306_fillRect(5, 48, 16, 16, BLACK);
}

bool WifiPainter::IsInterfaceUp(std::string ifname)
{
	std::ifstream t("/sys/class/net/wlan0/operstate");
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	return str == "up";
}
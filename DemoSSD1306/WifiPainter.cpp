#include <string>
#include <fstream>
#include <streambuf>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif
	#include "fonts.h"
	#include "WifiPainter.h"
#ifdef __cplusplus
}
#endif

WifiPainter::WifiPainter(OledDisplay *display)
{
	_display = display;
}


WifiPainter::~WifiPainter()
{
}

void WifiPainter::Draw()
{
	const std::string ifname("wlan0");

	if (WifiPainter::IsInterfaceUp(ifname))
		_display->DrawBitmap(0, 47, _imageWifi, 16, 16, WHITE, BLACK);
	else
		_display->FillRectangle(0, 47, 16, 16, BLACK);
}

bool WifiPainter::IsInterfaceUp(std::string ifname)
{
	std::ifstream t("/sys/class/net/wlan0/operstate");
	std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
	return  str.substr(0, 2) == "up";
}
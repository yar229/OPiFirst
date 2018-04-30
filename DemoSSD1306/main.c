///******
//Demo for ssd1306 i2c driver for  Raspberry Pi 
//******/
//
#include "ssd1306_i2c.h"
#include "fonts.h"

void main() 
{

	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	ssd1306_clearDisplay();
	//ssd1306_setTextSize(2);

	unsigned char* text = "Glcd english";
	ssd1306_drawString(fonts[0], text, 0, 0);

	unsigned char* text1 = u8"арусский Glcdru";
	ssd1306_drawString(fonts[1], text1, 0, 20);


	unsigned char* text2 = "English tahoma";
	ssd1306_drawString(fonts[2], text2, 0, 50);


	ssd1306_display();
	delay(5000);
	//ssd1306_dim(1);
	//ssd1306_startscrollleft(00,0xFF);

	
}


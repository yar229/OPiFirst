///******
//Demo for ssd1306 i2c driver for  Raspberry Pi 
//******/
//
#include "ssd1306_i2c.h"

void main() {

	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	ssd1306_clearDisplay();
	//ssd1306_setTextSize(2);

	char* text = "1рстуф1 Проверка работы oled экрана ssd1306 на    апельсинке";
	ssd1306_drawString(text);
	//ssd1306_drawChar
	ssd1306_display();
	delay(5000);
	ssd1306_dim(1);
	ssd1306_startscrollleft(00,0xFF);

	
}


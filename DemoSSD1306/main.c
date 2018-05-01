///******
//Demo for ssd1306 i2c driver for  Raspberry Pi 
//******/
//
#include "ssd1306_i2c.h"
#include "fonts.h"
#include "time.h"

int main()
{
	time_t timer;
	char datebuffer[100];
	char timebuffer[26];
	char secbuffer[4];
	struct tm* tm_info;

	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
	ssd1306_clearDisplay();

	while (1) 
	{
		time(&timer);
		tm_info = localtime(&timer);

		strftime(datebuffer, 100, "%Y-%m-%d", tm_info);
		strftime(timebuffer, 26, "%H:%M", tm_info);
		strftime(secbuffer, 4, "%S", tm_info);

		ssd1306_clearDisplay();

		ssd1306_drawString(fonts[2], datebuffer, 40, 5);
		ssd1306_drawString(fonts[4], timebuffer, 30, 15);
		ssd1306_drawString(fonts[2], secbuffer, 110, 15);

		ssd1306_display();

		delay(100);
	}

	
}



//void main() 
//{
//
//	ssd1306_begin(SSD1306_SWITCHCAPVCC, SSD1306_I2C_ADDRESS);
//	ssd1306_clearDisplay();
//	//ssd1306_setTextSize(2);
//
//	unsigned char* text3 = "Chiken";
//	ssd1306_drawString(fonts[3], text3, 0, 15);
//
//
//	unsigned char* text = "monster";
//	ssd1306_drawString(fonts[0], text, 0, 0);
//
//	//unsigned char* text1 = "1рстуф1 Проверка работы oled экрана ssd1306 на    апельсинке";;
//	//ssd1306_drawString(fonts[1], text1, 0, 20);
//
//
//	unsigned char* text2 = "killer";
//	ssd1306_drawString(fonts[2], text2, 0, 50);
//
//
//	ssd1306_display();
//	delay(5000);
//	//ssd1306_dim(1);
//	//ssd1306_startscrollleft(00,0xFF);
//
//	
//}
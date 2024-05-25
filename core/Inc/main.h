/*
 * main.h
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmkus
 */

#ifndef CORE_INC_MAIN_H_
#define CORE_INC_MAIN_H_

#include "GFX.h"
#include "LCD_ili932x.h"

class Main final
{
public:
	esp_err_t setup();
	void loop();

protected:

	void demoClear();

	void demoPixels();

	void demoLines();

	void demoFastLines();

	void demoRects();

	void demoFilledRects();

	void demoCircles();

	void demoFilledCircles();

	void demoChar();

	void demoImage();

	void demoArc();

private:
	LCD_ili932x *drv;
	GFX *lcd;

	uint16_t lcd_colors[25] =
	{
		LCD_COLOR_BLUE,
		LCD_COLOR_GREEN,
		LCD_COLOR_RED,
		LCD_COLOR_CYAN,
		LCD_COLOR_MAGENTA,
		LCD_COLOR_YELLOW,
		LCD_COLOR_LIGHTBLUE,
		LCD_COLOR_LIGHTGREEN,
		LCD_COLOR_LIGHTRED,
		LCD_COLOR_LIGHTCYAN,
		LCD_COLOR_LIGHTMAGENTA,
		LCD_COLOR_LIGHTYELLOW,
		LCD_COLOR_DARKBLUE,
		LCD_COLOR_DARKGREEN,
		LCD_COLOR_DARKRED,
		LCD_COLOR_DARKCYAN,
		LCD_COLOR_DARKMAGENTA,
		LCD_COLOR_DARKYELLOW,
		LCD_COLOR_WHITE,
		LCD_COLOR_LIGHTGRAY,
		LCD_COLOR_GRAY,
		LCD_COLOR_DARKGRAY,
		LCD_COLOR_BLACK,
		LCD_COLOR_BROWN,
		LCD_COLOR_ORANGE
	};

};

#endif /* CORE_INC_MAIN_H_ */

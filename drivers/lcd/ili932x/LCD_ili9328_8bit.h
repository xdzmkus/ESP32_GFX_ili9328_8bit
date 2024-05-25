/*
 * LCD_ili9328_8bit.h
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmk
 */

#ifndef DRIVERS_LCD_ILI932X_LCD_ILI9328_8BIT_H_
#define DRIVERS_LCD_ILI932X_LCD_ILI9328_8BIT_H_

#include "LCD_ili932x.h"
#include "LCD_IO_8bit.h"

class LCD_ili9328_8bit: public LCD_ili932x, protected LCD_IO_8bit
{
public:
	LCD_ili9328_8bit();
	virtual ~LCD_ili9328_8bit();

	uint16_t GetID();
};

#endif /* DRIVERS_LCD_ILI932X_LCD_ILI9328_8BIT_H_ */

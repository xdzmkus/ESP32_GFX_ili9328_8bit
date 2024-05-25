/*
 * LCD_ili9328_8bit.cpp
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmk
 */

#include "LCD_ili9328_8bit.h"

LCD_ili9328_8bit::LCD_ili9328_8bit()
{
}

LCD_ili9328_8bit::~LCD_ili9328_8bit()
{
}

inline uint16_t LCD_ili9328_8bit::GetID()
{
	return 0x9328;
}

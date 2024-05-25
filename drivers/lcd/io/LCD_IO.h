/*
 * LCD_IO.h
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmkus
 */

#ifndef DRIVERS_LCD_IO_LCD_IO_H_
#define DRIVERS_LCD_IO_LCD_IO_H_

#include <stdint.h>

class LCD_IO
{
public:
	LCD_IO() {};
	virtual ~LCD_IO() {};

	virtual void LCD_IO_Init(void) = 0;
	virtual void LCD_IO_Reset(void) = 0;

	virtual uint16_t LCD_IO_ReadReg(uint8_t Reg) = 0;

	virtual void LCD_IO_WriteReg(uint8_t Reg, uint16_t Data) = 0;
	virtual void LCD_IO_WriteRegN(uint8_t Reg, uint16_t Data, uint32_t Count) = 0;
	virtual void LCD_IO_WriteRegArray(uint8_t Reg, uint16_t *pData, uint32_t Size) = 0;
};

#endif /* DRIVERS_LCD_IO_LCD_IO_H_ */

/*
 * LCD_IO_8bit.h
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmkus
 */

#ifndef DRIVERS_LCD_IO_LCD_IO_8BIT_H_
#define DRIVERS_LCD_IO_LCD_IO_8BIT_H_

#include "LCD_IO.h"

class LCD_IO_8bit: public virtual LCD_IO
{
public:
	LCD_IO_8bit();
	virtual ~LCD_IO_8bit();

	virtual void LCD_IO_Init(void);
	virtual void LCD_IO_Reset(void);

	virtual uint16_t LCD_IO_ReadReg(uint8_t Reg);

	virtual void LCD_IO_WriteReg(uint8_t Reg, uint16_t Data);
	virtual void LCD_IO_WriteRegN(uint8_t Reg, uint16_t Data, uint32_t Count);
	virtual void LCD_IO_WriteRegArray(uint8_t Reg, uint16_t *pData, uint32_t Size);

protected:

	void LCD_SPI_Config_Output();

	void LCD_DB_Config_Output();
	void LCD_DB_Config_Input();

	void LCD_DB_WRITE(uint8_t Data);
	uint8_t LCD_DB_READ();
};

#endif /* DRIVERS_LCD_IO_LCD_IO_8BIT_H_ */

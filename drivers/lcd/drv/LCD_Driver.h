/*
 * LCD_Driver.h
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmkus
 */

#ifndef DRIVERS_LCD_IO_LCD_DRIVER_H_
#define DRIVERS_LCD_IO_LCD_DRIVER_H_

#include <stdint.h>

class LCD_Driver
{
public:
	LCD_Driver() {};
	virtual ~LCD_Driver() {};

	virtual uint16_t GetID() = 0;

	virtual uint16_t GetLcdPixelWidth(void) = 0;
	virtual uint16_t GetLcdPixelHeight(void) = 0;

	virtual uint16_t Init(void) = 0;
	virtual void Reset(void) = 0;
	virtual void Begin(void) = 0;

	virtual void Clear(uint16_t) = 0;
	virtual void DisplayOn(void) = 0;
	virtual void DisplayOff(void) = 0;
	virtual void SetRotation(uint8_t) = 0;
	virtual void SetCursor(uint16_t, uint16_t) = 0;
	virtual void SetDisplayWindow(uint16_t, uint16_t, uint16_t, uint16_t) = 0;

	virtual void WritePixel(uint16_t, uint16_t, uint16_t) = 0;
	virtual uint16_t ReadPixel(uint16_t, uint16_t) = 0;

	virtual void DrawHLine(int16_t, int16_t, uint16_t, uint16_t) = 0;
	virtual void DrawVLine(int16_t, int16_t, uint16_t, uint16_t) = 0;

	virtual void DrawBitmap(uint16_t, uint16_t, uint8_t*) = 0;
	virtual void DrawRGBImage(uint16_t, uint16_t, uint16_t*, uint32_t) = 0;

};

#endif /* DRIVERS_LCD_IO_LCD_DRIVER_H_ */

/*
 * LCD_ili932x.h
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmk
 */

#ifndef DRIVERS_LCD_ILI9328_LCD_ILI932X_H_
#define DRIVERS_LCD_ILI9328_LCD_ILI932X_H_

#include "LCD_Driver.h"
#include "LCD_IO.h"

class LCD_ili932x: public LCD_Driver, public virtual LCD_IO
{
public:
	LCD_ili932x();
	virtual ~LCD_ili932x();

	virtual uint16_t GetLcdPixelWidth(void);
	virtual uint16_t GetLcdPixelHeight(void);

	virtual uint16_t Init(void);
	virtual void Reset(void);
	virtual void Begin(void);

	virtual void Clear(uint16_t);
	virtual void DisplayOn(void);
	virtual void DisplayOff(void);
	virtual void SetRotation(uint8_t);
	virtual void SetCursor(uint16_t, uint16_t);
	virtual void SetDisplayWindow(uint16_t, uint16_t, uint16_t, uint16_t);

	virtual void WritePixel(uint16_t, uint16_t, uint16_t);
	virtual uint16_t ReadPixel(uint16_t, uint16_t);

	virtual void DrawHLine(int16_t, int16_t, uint16_t, uint16_t);
	virtual void DrawVLine(int16_t, int16_t, uint16_t, uint16_t);

	virtual void DrawBitmap(uint16_t, uint16_t, uint8_t*);
	virtual void DrawRGBImage(uint16_t, uint16_t, uint16_t*, uint32_t);

protected:

	uint8_t lcd_rotation = 0;
};

#endif /* DRIVERS_LCD_ILI9328_LCD_ILI932X_H_ */

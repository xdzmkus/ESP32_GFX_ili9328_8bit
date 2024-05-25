/*
 * GFX.h
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmkus
 */

#ifndef MAIN_GFX_H_
#define MAIN_GFX_H_

#include <stdint.h>

#include "fonts/fonts.h"
#include "LCD_Driver.h"

/**
  * @brief LCD default font
  */
#define LCD_DEFAULT_FONT         Font8

typedef struct
{
  uint16_t TextColor;
  uint16_t BackColor;
  sFONT    *pFont;

}LCD_DrawPropTypeDef;

typedef struct
{
  int16_t X;
  int16_t Y;

}Point, * pPoint;

/**
  * @brief  Line mode structures definition
  */
typedef enum
{
  CENTER_MODE             = 0x01,    /*!< Center mode */
  RIGHT_MODE              = 0x02,    /*!< Right mode  */
  LEFT_MODE               = 0x03     /*!< Left mode   */

}Line_ModeTypdef;

/**
  * @brief  LCD color
  */
#define LCD_COLOR_BLUE          0x001F
#define LCD_COLOR_GREEN         0x07E0
#define LCD_COLOR_RED           0xF800
#define LCD_COLOR_CYAN          0x07FF
#define LCD_COLOR_MAGENTA       0xF81F
#define LCD_COLOR_YELLOW        0xFFE0
#define LCD_COLOR_LIGHTBLUE     0x841F
#define LCD_COLOR_LIGHTGREEN    0x87F0
#define LCD_COLOR_LIGHTRED      0xFC10
#define LCD_COLOR_LIGHTCYAN     0x87FF
#define LCD_COLOR_LIGHTMAGENTA  0xFC1F
#define LCD_COLOR_LIGHTYELLOW   0xFFF0
#define LCD_COLOR_DARKBLUE      0x0010
#define LCD_COLOR_DARKGREEN     0x0400
#define LCD_COLOR_DARKRED       0x8000
#define LCD_COLOR_DARKCYAN      0x0410
#define LCD_COLOR_DARKMAGENTA   0x8010
#define LCD_COLOR_DARKYELLOW    0x8400
#define LCD_COLOR_WHITE         0xFFFF
#define LCD_COLOR_LIGHTGRAY     0xD69A
#define LCD_COLOR_GRAY          0x8410
#define LCD_COLOR_DARKGRAY      0x4208
#define LCD_COLOR_BLACK         0x0000
#define LCD_COLOR_BROWN         0xA145
#define LCD_COLOR_ORANGE        0xFD20

/**
  * @brief  LCD status structure definition
  */
#define LCD_OK         0x00
#define LCD_ERROR      0x01
#define LCD_TIMEOUT    0x02

#define MAX_HEIGHT_FONT         17
#define MAX_WIDTH_FONT          24
#define OFFSET_BITMAP           54

class GFX
{
public:
	GFX(LCD_Driver *driver);

	virtual ~GFX();

	static uint16_t RGB565(uint8_t r, uint8_t g, uint8_t b);

	uint8_t  Init(void);

	void     Clear(uint16_t Color);

	void     SetRotation(uint8_t rotation);

	void     SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);

	void     DisplayOn(void);
	void     DisplayOff(void);

	uint16_t GetWidth(void);
	uint16_t GetHeight(void);

	uint16_t GetTextColor(void);
	void     SetTextColor(uint16_t Color);
	uint16_t GetBackColor(void);
	void     SetBackColor(uint16_t Color);
	sFONT*   GetFont(void);
	void     SetFont(sFONT *fonts);

	void     DisplayChar(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);
	void     DisplayStringAtLine(uint16_t Line, uint8_t *ptr);
	void     DisplayStringAt(uint16_t Xpos, uint16_t Ypos, uint8_t *Text, Line_ModeTypdef Mode);
	void     ClearStringLine(uint16_t Line);

	uint16_t ReadPixel(uint16_t Xpos, uint16_t Ypos);
	void     DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode);
	void     DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2);
	void     DrawHLine(int16_t Xpos, int16_t Ypos, uint16_t Length);
	void     DrawVLine(int16_t Xpos, int16_t Ypos, uint16_t Length);
	void     DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
	void     DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
	void     DrawPolygon(pPoint Points, uint16_t PointCount);
	void     DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
	void     DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp);
	void     DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height, uint16_t *pbmp);

	void     FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
	void     FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
	void     FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
	void 	 FillArc(uint16_t centerX, uint16_t centerY, uint16_t outerRadius, uint16_t innerRadius, float startAngle, float endAngle);

private :

	LCD_Driver* lcd_drv;

	LCD_DrawPropTypeDef DrawProp;

	/* Max size of bitmap will based on a font24 (17x24) */
	uint8_t bitmap[MAX_HEIGHT_FONT * MAX_WIDTH_FONT * 2 + OFFSET_BITMAP] = { 0 };

};

#endif /* MAIN_GFX_H_ */

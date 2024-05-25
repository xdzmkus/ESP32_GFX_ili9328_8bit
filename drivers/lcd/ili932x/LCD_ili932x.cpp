/*
 * LCD_ili932x.cpp
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmkus
 */

#include "LCD_ili932x.h"

/**
 * @brief  ili932x Size
 */
#define  ili932x_LCD_PIXEL_WIDTH    ((uint16_t)240)
#define  ili932x_LCD_PIXEL_HEIGHT   ((uint16_t)320)

/**
 * @brief  ili932x Registers
 */
#define LCD_REG_0             0x00
#define LCD_REG_1             0x01
#define LCD_REG_2             0x02
#define LCD_REG_3             0x03
#define LCD_REG_4             0x04
#define LCD_REG_7             0x07
#define LCD_REG_8             0x08
#define LCD_REG_9             0x09
#define LCD_REG_10            0x0A
#define LCD_REG_12            0x0C
#define LCD_REG_13            0x0D
#define LCD_REG_15            0x0F
#define LCD_REG_16            0x10
#define LCD_REG_17            0x11
#define LCD_REG_18            0x12
#define LCD_REG_19            0x13
#define LCD_REG_32            0x20
#define LCD_REG_33            0x21
#define LCD_REG_34            0x22
#define LCD_REG_41            0x29
#define LCD_REG_43            0x2B
#define LCD_REG_48            0x30
#define LCD_REG_49            0x31
#define LCD_REG_50            0x32
#define LCD_REG_53            0x35
#define LCD_REG_54            0x36
#define LCD_REG_55            0x37
#define LCD_REG_56            0x38
#define LCD_REG_57            0x39
#define LCD_REG_60            0x3C
#define LCD_REG_61            0x3D
#define LCD_REG_80            0x50
#define LCD_REG_81            0x51
#define LCD_REG_82            0x52
#define LCD_REG_83            0x53
#define LCD_REG_96            0x60
#define LCD_REG_97            0x61
#define LCD_REG_106           0x6A
#define LCD_REG_128           0x80
#define LCD_REG_129           0x81
#define LCD_REG_130           0x82
#define LCD_REG_131           0x83
#define LCD_REG_132           0x84
#define LCD_REG_133           0x85
#define LCD_REG_144           0x90
#define LCD_REG_146           0x92
#define LCD_REG_147           0x93
#define LCD_REG_149           0x95
#define LCD_REG_151           0x97
#define LCD_REG_152           0x98
#define LCD_REG_161           0xA1
#define LCD_REG_162           0xA2
#define LCD_REG_165           0xA5

LCD_ili932x::LCD_ili932x()
{
}

LCD_ili932x::~LCD_ili932x()
{
}

/**
 * @brief  Get the LCD pixel Width.
 * @param  None
 * @retval The Lcd Pixel Width
 */
inline uint16_t LCD_ili932x::GetLcdPixelWidth(void)
{
	return lcd_rotation % 2 == 0 ?
	ili932x_LCD_PIXEL_WIDTH :
									ili932x_LCD_PIXEL_HEIGHT;
}

/**
 * @brief  Get the LCD pixel Height.
 * @param  None
 * @retval The Lcd Pixel Height
 */
inline uint16_t LCD_ili932x::GetLcdPixelHeight(void)
{
	return lcd_rotation % 2 == 0 ?
	ili932x_LCD_PIXEL_HEIGHT :
									ili932x_LCD_PIXEL_WIDTH;
}

/**
 * @brief  Initialize the ili932x LCD Component.
 * @param  None
 * @retval None
 */
uint16_t LCD_ili932x::Init(void)
{
	LCD_IO_Init();

	LCD_IO_Reset();

	LCD_IO_WriteReg(LCD_REG_0, 0x0001);

	uint16_t id = LCD_IO_ReadReg(LCD_REG_0);

	return id;
}

/**
 * @brief  Reset the ili932x LCD Component.
 * @param  None
 * @retval None
 */
void LCD_ili932x::Reset(void)
{
	LCD_IO_Reset();
}

/**
 * @brief  Begin with the ili932x LCD module.
 * @param  None
 * @retval None
 */
void LCD_ili932x::Begin(void)
{
	/* Start Initial Sequence --------------------------------------------------*/
	LCD_IO_WriteReg(LCD_REG_0, 0x0001); /* Start internal OSC. */
	LCD_IO_WriteReg(LCD_REG_1, 0x0100); /* Set SS and SM bit */
	LCD_IO_WriteReg(LCD_REG_2, 0x0700); /* Set 1 line inversion */

	SetRotation(lcd_rotation);

	LCD_IO_WriteReg(LCD_REG_4, 0x0000); /* Resize register */
	LCD_IO_WriteReg(LCD_REG_8, 0x0302); /* Set the back porch and front porch */
	LCD_IO_WriteReg(LCD_REG_9, 0x0000); /* Set non-display area refresh cycle ISC[3:0] */
	LCD_IO_WriteReg(LCD_REG_10, 0x0000); /* FMARK function */
	LCD_IO_WriteReg(LCD_REG_12, 0x0000); /* RGB interface setting */
	LCD_IO_WriteReg(LCD_REG_13, 0x0000); /* Frame marker Position */
	LCD_IO_WriteReg(LCD_REG_15, 0x0000); /* RGB interface polarity */

	DisplayOn();

	/* Adjust the Gamma Curve (ili932x) ----------------------------------------*/
	LCD_IO_WriteReg(LCD_REG_48, 0x0000);
	LCD_IO_WriteReg(LCD_REG_49, 0x0107);
	LCD_IO_WriteReg(LCD_REG_50, 0x0000);
	LCD_IO_WriteReg(LCD_REG_53, 0x0203);
	LCD_IO_WriteReg(LCD_REG_54, 0x0402);
	LCD_IO_WriteReg(LCD_REG_55, 0x0000);
	LCD_IO_WriteReg(LCD_REG_56, 0x0207);
	LCD_IO_WriteReg(LCD_REG_57, 0x0000);
	LCD_IO_WriteReg(LCD_REG_60, 0x0203);
	LCD_IO_WriteReg(LCD_REG_61, 0x0403);

	SetDisplayWindow(0, 0, GetLcdPixelWidth(), GetLcdPixelHeight());

	/* Set GRAM area -----------------------------------------------------------*/
	LCD_IO_WriteReg(LCD_REG_96, 0xA700); /* Gate Scan Line(GS=1, scan direction is G320~G1) */
	LCD_IO_WriteReg(LCD_REG_97, 0x0003); /* NDL,VLE, REV */
	LCD_IO_WriteReg(LCD_REG_106, 0x0000); /* set scrolling line */

	/* Partial Display Control -------------------------------------------------*/
	LCD_IO_WriteReg(LCD_REG_128, 0x0000);
	LCD_IO_WriteReg(LCD_REG_129, 0x0000);
	LCD_IO_WriteReg(LCD_REG_130, 0x0000);
	LCD_IO_WriteReg(LCD_REG_131, 0x0000);
	LCD_IO_WriteReg(LCD_REG_132, 0x0000);
	LCD_IO_WriteReg(LCD_REG_133, 0x0000);

	/* Panel Control -----------------------------------------------------------*/
	LCD_IO_WriteReg(LCD_REG_144, 0x0010);
	LCD_IO_WriteReg(LCD_REG_146, 0x0000);
	LCD_IO_WriteReg(LCD_REG_147, 0x0003);
	LCD_IO_WriteReg(LCD_REG_149, 0x0110);
	LCD_IO_WriteReg(LCD_REG_151, 0x0000);
	LCD_IO_WriteReg(LCD_REG_152, 0x0000);

	SetCursor(0, 0);
}

void LCD_ili932x::Clear(uint16_t RGBCode)
{
	SetDisplayWindow(0, 0, GetLcdPixelWidth(), GetLcdPixelHeight());

	SetCursor(0, 0);

	LCD_IO_WriteRegN(LCD_REG_34, RGBCode,
	ili932x_LCD_PIXEL_WIDTH * ili932x_LCD_PIXEL_HEIGHT);
}

/**
 * @brief  Enables the Display.
 * @param  None
 * @retval None
 */
void LCD_ili932x::DisplayOn(void)
{
	/* Power On sequence -------------------------------------------------------*/
	LCD_IO_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	LCD_IO_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
	LCD_IO_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
	LCD_IO_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude*/
	//LCD_Delay(20);
	LCD_IO_WriteReg(LCD_REG_16, 0x14B0); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	//LCD_Delay(5);
	LCD_IO_WriteReg(LCD_REG_17, 0x0007); /* DC1[2:0], DC0[2:0], VC[2:0] */
	//LCD_Delay(5);
	LCD_IO_WriteReg(LCD_REG_18, 0x0018); /* VREG1OUT voltage */
	//LCD_Delay(5);
	LCD_IO_WriteReg(LCD_REG_19, 0x1000); /* VDV[4:0] for VCOM amplitude */
	LCD_IO_WriteReg(LCD_REG_41, 0x0015); /* VCM[4:0] for VCOMH */
	//LCD_Delay(5);

	/* Display On */
	LCD_IO_WriteReg(LCD_REG_7, 0x0133); /* 262K color and display ON */
	//LCD_Delay(50);
}

/**
 * @brief  Disables the Display.
 * @param  None
 * @retval None
 */
void LCD_ili932x::DisplayOff(void)
{
	/* Power Off sequence ------------------------------------------------------*/
	LCD_IO_WriteReg(LCD_REG_16, 0x0000); /* SAP, BT[3:0], AP, DSTB, SLP, STB */
	LCD_IO_WriteReg(LCD_REG_17, 0x0000); /* DC1[2:0], DC0[2:0], VC[2:0] */
	LCD_IO_WriteReg(LCD_REG_18, 0x0000); /* VREG1OUT voltage */
	LCD_IO_WriteReg(LCD_REG_19, 0x0000); /* VDV[4:0] for VCOM amplitude*/

	LCD_IO_WriteReg(LCD_REG_41, 0x0000); /* VCM[4:0] for VCOMH */

	/* Display Off */
	LCD_IO_WriteReg(LCD_REG_7, 0x0);
}

void LCD_ili932x::SetRotation(uint8_t rotation)
{
	lcd_rotation = rotation;

	/* set GRAM write direction and BGR = 1 */
	/* (D5:D4) I/D[1:0] = 00 Horizontal:decrement  Vertical:decrement */
	/* (D5:D4) I/D[1:0] = 01 Horizontal:increment  Vertical:decrement */
	/* (D5:D4) I/D[1:0] = 10 Horizontal:decrement  Vertical:increment */
	/* (D5:D4) I/D[1:0] = 11 Horizontal:increment  Vertical:increment */
	/* (D3) AM=0 (the address is updated in horizontal writing direction) */
	/* (D3) AM=1 (the address is updated in vertical writing direction) */
	switch (rotation % 4)
	{
	case 0:
		LCD_IO_WriteReg(LCD_REG_3, 0x1030);
		break;
	case 1:
		LCD_IO_WriteReg(LCD_REG_3, 0x1018);
		break;
	case 2:
		LCD_IO_WriteReg(LCD_REG_3, 0x1000);
		break;
	case 3:
		LCD_IO_WriteReg(LCD_REG_3, 0x1028);
		break;
	default:
		break;
	}
}

/**
 * @brief  Set Cursor position.
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @retval None
 */
void LCD_ili932x::SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	if (Xpos >= GetLcdPixelWidth() || Ypos >= GetLcdPixelHeight())
		return;

	uint16_t x = 0;
	uint16_t y = 0;

	switch (lcd_rotation % 4)
	{
	case 0:
		x = Xpos;
		y = Ypos;
		break;
	case 1:
		x = Ypos;
		y = ili932x_LCD_PIXEL_HEIGHT - 1 - Xpos;
		break;
	case 2:
		x = ili932x_LCD_PIXEL_WIDTH - 1 - Xpos;
		y = ili932x_LCD_PIXEL_HEIGHT - 1 - Ypos;
		break;
	case 3:
		x = ili932x_LCD_PIXEL_WIDTH - 1 - Ypos;
		;
		y = Xpos;
		break;
	default:
		break;
	}

	LCD_IO_WriteReg(LCD_REG_32, x);
	LCD_IO_WriteReg(LCD_REG_33, y);
}

/**
 * @brief  Sets a display window
 * @param  Xpos:   specifies the X bottom left position.
 * @param  Ypos:   specifies the Y bottom left position.
 * @param  Height: display window height.
 * @param  Width:  display window width.
 * @retval None
 */
void LCD_ili932x::SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width,
		uint16_t Height)
{
	if (Xpos >= GetLcdPixelWidth() || Ypos >= GetLcdPixelHeight())
		return;

	if (Xpos + Width > GetLcdPixelWidth()
			|| Ypos + Height > GetLcdPixelHeight())
		return;

	uint16_t x1 = 0;
	uint16_t y1 = 0;
	uint16_t x2 = ili932x_LCD_PIXEL_WIDTH;
	uint16_t y2 = ili932x_LCD_PIXEL_HEIGHT;

	switch (lcd_rotation % 4)
	{
	case 0:
		x1 = Xpos;
		y1 = Ypos;
		x2 = Xpos + Width;
		y2 = Ypos + Height;
		break;
	case 1:
		x1 = Ypos;
		y1 = ili932x_LCD_PIXEL_HEIGHT - Width - Xpos;
		x2 = Ypos + Height;
		y2 = ili932x_LCD_PIXEL_HEIGHT - Xpos;
		break;
	case 2:
		x1 = ili932x_LCD_PIXEL_WIDTH - Width - Xpos;
		y1 = ili932x_LCD_PIXEL_HEIGHT - Height - Ypos;
		x2 = ili932x_LCD_PIXEL_WIDTH - Xpos;
		y2 = ili932x_LCD_PIXEL_HEIGHT - Ypos;
		break;
	case 3:
		x1 = ili932x_LCD_PIXEL_WIDTH - Height - Ypos;
		y1 = Xpos;
		x2 = ili932x_LCD_PIXEL_WIDTH - Ypos;
		y2 = Xpos + Width;
		break;
	default:
		break;
	}

	/* Horizontal GRAM Start Address */
	LCD_IO_WriteReg(LCD_REG_80, x1);
	/* Horizontal GRAM End Address */
	LCD_IO_WriteReg(LCD_REG_81, x2 - 1);

	/* Vertical GRAM Start Address */
	LCD_IO_WriteReg(LCD_REG_82, y1);
	/* Vertical GRAM End Address */
	LCD_IO_WriteReg(LCD_REG_83, y2 - 1);
}

/**
 * @brief  Write pixel.
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @param  RGBCode: the RGB pixel color
 * @retval None
 */
void LCD_ili932x::WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode)
{
	if (Xpos >= GetLcdPixelWidth() || Ypos >= GetLcdPixelHeight())
		return;

	/* Set Cursor */
	SetCursor(Xpos, Ypos);

	/* Prepare to write GRAM */
	LCD_IO_WriteReg(LCD_REG_34, RGBCode);
}

/**
 * @brief  Read pixel.
 * @param  None
 * @retval The RGB pixel color
 */
uint16_t LCD_ili932x::ReadPixel(uint16_t Xpos, uint16_t Ypos)
{
	if (Xpos >= GetLcdPixelWidth() || Ypos >= GetLcdPixelHeight())
		return 0;

	/* Set Cursor */
	SetCursor(Xpos, Ypos);

	/* Read 16-bit Reg */
	return LCD_IO_ReadReg(LCD_REG_34);
}

/**
 * @brief  Draw vertical line.
 * @param  Xpos:     specifies the X position.
 * @param  Ypos:     specifies the Y position.
 * @param  Length:   specifies the Line length.
 * @param  RGBCode:  specifies the RGB color
 * @retval None
 */
void LCD_ili932x::DrawHLine(int16_t Xpos, int16_t Ypos, uint16_t Length,
		uint16_t RGBCode)
{
	if (Ypos < 0 || Xpos >= GetLcdPixelWidth() || Ypos >= GetLcdPixelHeight())
		return;

	int16_t newLength = Length;

	if (Xpos < 0)
	{
		newLength += Xpos;
		if (newLength <= 0)
			return;
		Xpos = 0;
	}
	else if (Xpos + Length > GetLcdPixelWidth())
	{
		newLength = GetLcdPixelWidth() - Xpos;
	}

	/* Set Cursor */
	SetCursor(Xpos, Ypos);

	/* Write 16-bit GRAM Reg */
	LCD_IO_WriteRegN(LCD_REG_34, RGBCode, newLength);
}

/**
 * @brief  Draw vertical line.
 * @param  Xpos:     specifies the X position.
 * @param  Ypos:     specifies the Y position.
 * @param  Length:   specifies the Line length.
 * @param  RGBCode:  specifies the RGB color
 * @retval None
 */
void LCD_ili932x::DrawVLine(int16_t Xpos, int16_t Ypos, uint16_t Length,
		uint16_t RGBCode)
{
	if (Xpos < 0 || Xpos >= GetLcdPixelWidth() || Ypos >= GetLcdPixelHeight())
		return;

	int16_t newLength = Length;

	if (Ypos < 0)
	{
		newLength += Ypos;
		if (newLength <= 0)
			return;
		Ypos = 0;
	}
	else if (Ypos + Length > GetLcdPixelHeight())
	{
		newLength = GetLcdPixelHeight() - Ypos;
	}

	/* Set Cursor */
	SetCursor(Xpos, Ypos);

	// save direction
	uint16_t direction = LCD_IO_ReadReg(LCD_REG_3);

	// invert direction
	LCD_IO_WriteReg(LCD_REG_3, direction ^ 0b1000);

	/* Write 16-bit GRAM Reg */
	LCD_IO_WriteRegN(LCD_REG_34, RGBCode, Length);

	// restore direction
	LCD_IO_WriteReg(LCD_REG_3, direction);
}

/**
 * @brief  Displays a bitmap picture.
 * @param  BmpAddress: Bmp picture address.
 * @param  Xpos: Bmp X position in the LCD
 * @param  Ypos: Bmp Y position in the LCD
 * @retval None
 */
void LCD_ili932x::DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp)
{
	uint32_t index = 0, size = 0;
	/* Read bitmap size */
	size = *(volatile uint16_t*) (pbmp + 2);
	size |= (*(volatile uint16_t*) (pbmp + 4)) << 16;
	/* Get bitmap data address offset */
	index = *(volatile uint16_t*) (pbmp + 10);
	index |= (*(volatile uint16_t*) (pbmp + 12)) << 16;
	size = (size - index) / 2;
	pbmp += index;

	/* Set Cursor */
	SetCursor(Xpos, Ypos);

	/* Write 16-bit GRAM Reg */
	LCD_IO_WriteRegArray(LCD_REG_34, (uint16_t*) pbmp, size);
}

/**
 * @brief  Displays picture.
 * @param  Xpos: Image X position in the LCD
 * @param  Ypos: Image Y position in the LCD
 * @param  pdata: picture address.
 * @param  Size: Image size in the LCD
 * @retval None
 */
void LCD_ili932x::DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t *pdata,
		uint32_t Size)
{
	/* Set Cursor */
	SetCursor(Xpos, Ypos);

	/* Write 16-bit GRAM Reg */
	LCD_IO_WriteRegArray(LCD_REG_34, pdata, Size);
}


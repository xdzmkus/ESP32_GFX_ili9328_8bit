/*
 * LCD_IO_8bit.cpp
 *
 *  Created on: 23 мая 2024 г.
 *      Author: xdzmkus
 */

#include "LCD_IO_8bit.h"

#include <driver/gpio.h>

#define LCD_RST_GPIO CONFIG_LCD_RST_GPIO
#define LCD_CS_GPIO  CONFIG_LCD_CS_GPIO
#define LCD_RS_GPIO  CONFIG_LCD_RS_GPIO
#define LCD_WR_GPIO  CONFIG_LCD_WR_GPIO
#define LCD_RD_GPIO  CONFIG_LCD_RD_GPIO
#define LCD_DB0_GPIO CONFIG_LCD_DB0_GPIO
#define LCD_DB1_GPIO CONFIG_LCD_DB1_GPIO
#define LCD_DB2_GPIO CONFIG_LCD_DB2_GPIO
#define LCD_DB3_GPIO CONFIG_LCD_DB3_GPIO
#define LCD_DB4_GPIO CONFIG_LCD_DB4_GPIO
#define LCD_DB5_GPIO CONFIG_LCD_DB5_GPIO
#define LCD_DB6_GPIO CONFIG_LCD_DB6_GPIO
#define LCD_DB7_GPIO CONFIG_LCD_DB7_GPIO

#define SPI_PIN_SEL \
			((1ULL<<LCD_CS_GPIO) | \
			(1ULL<<LCD_RS_GPIO) | \
			(1ULL<<LCD_RD_GPIO) | \
			(1ULL<<LCD_WR_GPIO) | \
			(1ULL<<LCD_RST_GPIO))
#define DB_PIN_SEL \
		    ((1ULL<<LCD_DB0_GPIO) | \
			(1ULL<<LCD_DB1_GPIO) | \
			(1ULL<<LCD_DB2_GPIO) | \
			(1ULL<<LCD_DB3_GPIO) | \
			(1ULL<<LCD_DB4_GPIO) | \
			(1ULL<<LCD_DB5_GPIO) | \
			(1ULL<<LCD_DB6_GPIO) | \
			(1ULL<<LCD_DB7_GPIO))

#define LCD_RST_0 gpio_set_level(static_cast<gpio_num_t>(LCD_RST_GPIO), 0)
#define LCD_RST_1 gpio_set_level(static_cast<gpio_num_t>(LCD_RST_GPIO), 1)
#define LCD_CS_0 gpio_set_level(static_cast<gpio_num_t>(LCD_CS_GPIO), 0)
#define LCD_CS_1 gpio_set_level(static_cast<gpio_num_t>(LCD_CS_GPIO), 1)
#define LCD_RS_0 gpio_set_level(static_cast<gpio_num_t>(LCD_RS_GPIO), 0)
#define LCD_RS_1 gpio_set_level(static_cast<gpio_num_t>(LCD_RS_GPIO), 1)
#define LCD_WR_0 gpio_set_level(static_cast<gpio_num_t>(LCD_WR_GPIO), 0)
#define LCD_WR_1 gpio_set_level(static_cast<gpio_num_t>(LCD_WR_GPIO), 1)
#define LCD_RD_0 gpio_set_level(static_cast<gpio_num_t>(LCD_RD_GPIO), 0)
#define LCD_RD_1 gpio_set_level(static_cast<gpio_num_t>(LCD_RD_GPIO), 1)


LCD_IO_8bit::LCD_IO_8bit()
{
}

LCD_IO_8bit::~LCD_IO_8bit()
{
}

void LCD_IO_8bit::LCD_SPI_Config_Output()
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = SPI_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //for powersave reasons, the GPIO should not be floating, select pullup
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
}

void LCD_IO_8bit::LCD_DB_Config_Output()
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = DB_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //for powersave reasons, the GPIO should not be floating, select pullup
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
}

void LCD_IO_8bit::LCD_DB_Config_Input()
{
    //zero-initialize the config structure.
    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as input mode
    io_conf.mode = GPIO_MODE_INPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = DB_PIN_SEL;
    //disable pull-down mode
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    //enable pull-up mode
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
}

inline void LCD_IO_8bit::LCD_DB_WRITE(uint8_t Data)
{
	gpio_set_level(static_cast<gpio_num_t>(LCD_DB0_GPIO), (Data & 1));
	gpio_set_level(static_cast<gpio_num_t>(LCD_DB1_GPIO), (Data >> 1) & 1);
	gpio_set_level(static_cast<gpio_num_t>(LCD_DB2_GPIO), (Data >> 2) & 1);
	gpio_set_level(static_cast<gpio_num_t>(LCD_DB3_GPIO), (Data >> 3) & 1);
	gpio_set_level(static_cast<gpio_num_t>(LCD_DB4_GPIO), (Data >> 4) & 1);
	gpio_set_level(static_cast<gpio_num_t>(LCD_DB5_GPIO), (Data >> 5) & 1);
	gpio_set_level(static_cast<gpio_num_t>(LCD_DB6_GPIO), (Data >> 6) & 1);
	gpio_set_level(static_cast<gpio_num_t>(LCD_DB7_GPIO), (Data >> 7) & 1);
}

inline uint8_t LCD_IO_8bit::LCD_DB_READ()
{
	struct DATA_BYTE {
	    unsigned int bit0 : 1;
	    unsigned int bit1 : 1;
	    unsigned int bit2 : 1;
	    unsigned int bit3 : 1;
	    unsigned int bit4 : 1;
	    unsigned int bit5 : 1;
	    unsigned int bit6 : 1;
	    unsigned int bit7 : 1;
	} Data;

	Data.bit0 = gpio_get_level(static_cast<gpio_num_t>(LCD_DB0_GPIO));
	Data.bit1 = gpio_get_level(static_cast<gpio_num_t>(LCD_DB1_GPIO));
	Data.bit2 = gpio_get_level(static_cast<gpio_num_t>(LCD_DB2_GPIO));
	Data.bit3 = gpio_get_level(static_cast<gpio_num_t>(LCD_DB3_GPIO));
	Data.bit4 = gpio_get_level(static_cast<gpio_num_t>(LCD_DB4_GPIO));
	Data.bit5 = gpio_get_level(static_cast<gpio_num_t>(LCD_DB5_GPIO));
	Data.bit6 = gpio_get_level(static_cast<gpio_num_t>(LCD_DB6_GPIO));
	Data.bit7 = gpio_get_level(static_cast<gpio_num_t>(LCD_DB7_GPIO));

	return *(uint8_t*)&Data;
}

void LCD_IO_8bit::LCD_IO_Init(void)
{
	LCD_SPI_Config_Output();

    LCD_DB_Config_Output();
}

void LCD_IO_8bit::LCD_IO_Reset(void)
{
	LCD_RST_0;
	LCD_RST_1;

	LCD_CS_1;
	LCD_RS_1;
	LCD_RD_1;
	LCD_WR_1;

	LCD_CS_0;
	LCD_RS_0;

	for (uint8_t i = 0; i < 4; i++)
	{
		LCD_DB_WRITE(0x00);
		LCD_WR_0;
		LCD_WR_1;
	}

	LCD_RS_1;
	LCD_CS_1;
}

//========================================================================
// **                                                                    **
// ** nCS       ----\__________________________________________/-------  **
// ** RS        ------\____________/-----------------------------------  **
// ** nRD       -------------------------\_____/-----------------------  **
// ** nWR       --------\_______/--------------------------------------  **
// ** DB[0:8]   ---------[index]----------[data]-----------------------  **
// **                                                                    **
//========================================================================
uint16_t LCD_IO_8bit::LCD_IO_ReadReg(uint8_t Reg)
{
	uint32_t readvalue = 0;

	LCD_CS_0;

	// write register index
	LCD_RS_0;
	LCD_RD_1;
	LCD_DB_WRITE(0x00); // write 0x00
	LCD_WR_0;
	LCD_WR_1;
	LCD_DB_WRITE(Reg); // write index
	LCD_WR_0;
	LCD_WR_1;
	LCD_RS_1;

	// read data
	LCD_DB_Config_Input();

	LCD_RD_0;
	readvalue = LCD_DB_READ();
	LCD_RD_1;

	readvalue <<= 8;

	LCD_RD_0;
	readvalue |= LCD_DB_READ();
	LCD_RD_1;

	LCD_CS_1;

	LCD_DB_Config_Output();

	return readvalue;
}

/************************************************************************
 **                                                                    **
 ** nCS       ----\__________________________________________/-------  **
 ** RS        ------\____________/-----------------------------------  **
 ** nRD       -------------------------------------------------------  **
 ** nWR       --------\_______/--------\_____/-----------------------  **
 ** DB[0:8]   ---------[index]----------[data]-----------------------  **
 **                                                                    **
 ************************************************************************/
void LCD_IO_8bit::LCD_IO_WriteReg(uint8_t Reg, uint16_t Data)
{
	LCD_CS_0;

	// write register index
	LCD_RS_0;
	LCD_RD_1;
	LCD_DB_WRITE(0x00); // write 0x00
	LCD_WR_0;
	LCD_WR_1;
	LCD_DB_WRITE(Reg); // write index
	LCD_WR_0;
	LCD_WR_1;
	LCD_RS_1;

	// write register data
	LCD_DB_WRITE(Data >> 8); // write high byte data
	LCD_WR_0;
	LCD_WR_1;
	LCD_DB_WRITE(Data & 0x00ff); // write low byte data
	LCD_WR_0;
	LCD_WR_1;

	LCD_CS_1;
}
void LCD_IO_8bit::LCD_IO_WriteRegN(uint8_t Reg, uint16_t Data, uint32_t Count)
{
	LCD_CS_0;

	// write register index
	LCD_RS_0;
	LCD_RD_1;
	LCD_DB_WRITE(0x00); // write 0x00
	LCD_WR_0;
	LCD_WR_1;
	LCD_DB_WRITE(Reg); // write index
	LCD_WR_0;
	LCD_WR_1;
	LCD_RS_1;

	// write register data
	for(uint32_t index=0; index < Count; index++)
	{
		LCD_DB_WRITE(Data >> 8); // write high byte data
		LCD_WR_0;
		LCD_WR_1;
		LCD_DB_WRITE(Data & 0x00ff); // write low byte data
		LCD_WR_0;
		LCD_WR_1;
	}

	LCD_CS_1;
}
void LCD_IO_8bit::LCD_IO_WriteRegArray(uint8_t Reg, uint16_t *pData, uint32_t Size)
{
	LCD_CS_0;

	// write register index
	LCD_RS_0;
	LCD_RD_1;
	LCD_DB_WRITE(0x00); // write 0x00
	LCD_WR_0;
	LCD_WR_1;
	LCD_DB_WRITE(Reg); // write index
	LCD_WR_0;
	LCD_WR_1;
	LCD_RS_1;

	// write register data
	for(uint32_t index=0; index < Size; index++)
	{
		LCD_DB_WRITE(pData[index] >> 8); // write high byte data
		LCD_WR_0;
		LCD_WR_1;
		LCD_DB_WRITE(pData[index] & 0x00ff); // write low byte data
		LCD_WR_0;
		LCD_WR_1;
	}

	LCD_CS_1;
}

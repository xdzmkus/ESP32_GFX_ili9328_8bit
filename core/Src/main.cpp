#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <unistd.h>
#include <algorithm>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "sdkconfig.h"

#include "main.h"

#include "LCD_ili9328_8bit.h"

static Main mainApp;

extern uint8_t stm32_mini_map[];

extern "C" void app_main(void)
{
	ESP_ERROR_CHECK(mainApp.setup());

	while (true)
	{
		mainApp.loop();
	}
}

esp_err_t Main::setup()
{
	esp_err_t status{ESP_OK};

	drv = new LCD_ili9328_8bit();
	lcd = new GFX(drv);

	if (lcd->Init())
		status = ESP_FAIL;

	return status;
}

void Main::loop()
{
	lcd->Clear(LCD_COLOR_BLACK);

	demoClear();

	demoPixels();

	demoLines();

	demoFastLines();

	demoRects();

	demoFilledRects();

	demoCircles();

	demoFilledCircles();

	demoChar();

	demoImage();

	demoArc();

	for (int i = 10; i >= 0; i--)
	{
		printf("Restarting in %d seconds...\n", i);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	printf("Restarting now.\n");
	fflush(stdout);
	esp_restart();
}

void Main::demoClear()
{
	for (uint8_t r = 0; r < 25; r++)
	{
		vTaskDelay(1000 / portTICK_PERIOD_MS);

		lcd->SetRotation(r);

		lcd->Clear(lcd_colors[r]);
	}
}

void Main::demoPixels()
{
	static uint16_t color = -1;

	for (uint8_t r = 0; r < 4; r++)
	{
		lcd->SetRotation(r);

		for (uint16_t y = 0; y < lcd->GetHeight(); ++y)
		{
			for (uint16_t x = 0; x < lcd->GetWidth(); ++x)
			{
				lcd->DrawPixel(x, y, color--);
			}
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Main::demoLines()
{
	lcd->SetTextColor(LCD_COLOR_WHITE);

	for (uint8_t r = 0; r < 4; r++)
	{
		lcd->SetRotation(r);

		lcd->Clear(LCD_COLOR_BLACK);

		for (uint16_t x = 0; x < lcd->GetWidth(); x += 6)
		{
			lcd->DrawLine(0, 0, x, lcd->GetHeight() - 1);
		}
		for (uint16_t y = 0; y < lcd->GetHeight(); y += 6)
		{
			lcd->DrawLine(0, 0, lcd->GetWidth() - 1, y);
		}

		lcd->Clear(LCD_COLOR_BLUE);

		int16_t startX = lcd->GetWidth() / 2 - lcd->GetWidth();
		int16_t endX = lcd->GetWidth() / 2 + lcd->GetWidth();

		int16_t startY = lcd->GetHeight() / 2 - lcd->GetHeight();
		int16_t endY = lcd->GetHeight() / 2 + lcd->GetHeight();

		for (int16_t y = startY; y < endY; y += 6)
		{
			lcd->DrawLine(startX, y, endX, lcd->GetHeight() - y);
		}

		for (int16_t x = startX; x < endX; x += 6)
		{
			lcd->DrawLine(x, endY, lcd->GetWidth() - x, startY);
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Main::demoFastLines()
{
	for (uint8_t r = 0; r < 4; r++)
	{
		lcd->SetRotation(r);

		lcd->Clear(LCD_COLOR_WHITE);

		lcd->SetTextColor(LCD_COLOR_RED);

		for (int16_t y = -10; y < lcd->GetHeight(); y += 10)
		{
			lcd->DrawHLine(0, y, lcd->GetWidth());
		}

		lcd->SetTextColor(LCD_COLOR_GREEN);

		for (int16_t x = -10; x < lcd->GetWidth(); x += 10)
		{
			lcd->DrawVLine(x, 0, lcd->GetHeight());
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Main::demoRects()
{
	for (uint8_t r = 0; r < 4; r++)
	{
		lcd->SetRotation(r);

		lcd->Clear(LCD_COLOR_WHITE);

		lcd->SetTextColor(lcd_colors[r]);

		uint16_t cx = lcd->GetWidth() / 2;
		uint16_t cy = lcd->GetHeight() / 2;

		uint16_t n = std::min(lcd->GetWidth(), lcd->GetHeight());

		for (uint16_t i = 2; i < n; i += 6)
		{
			uint16_t i2 = i / 2;
			lcd->DrawRect(cx - i2, cy - i2, i, i);
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Main::demoFilledRects()
{
	for (uint8_t r = 0; r < 4; r++)
	{
		lcd->SetRotation(r);

		lcd->Clear(LCD_COLOR_WHITE);

		lcd->SetTextColor(lcd_colors[r]);

		uint16_t cx = lcd->GetWidth() / 2;
		uint16_t cy = lcd->GetHeight() / 2;

		uint16_t n = std::min(lcd->GetWidth(), lcd->GetHeight());

		for (uint16_t i = 2; i < n; i += 6)
		{
			uint16_t i2 = i / 2;
			lcd->FillRect(cx - i2, cy - i2, i, i);
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Main::demoCircles()
{
	for (uint8_t r = 0; r < 4; r++)
	{
		lcd->SetRotation(r);

		lcd->Clear(LCD_COLOR_WHITE);

		lcd->SetTextColor(lcd_colors[r]);

		uint16_t r1 = 10;
		uint16_t r2 = 20;

		uint16_t w = lcd->GetWidth() + r1;
		uint16_t h = lcd->GetHeight() + r1;

		for (uint16_t x = r1; x < w; x += r2)
		{
			for (uint16_t y = r1; y < h; y += r2)
			{
				lcd->DrawCircle(x, y, r1);
			}
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Main::demoFilledCircles()
{
	for (uint8_t r = 0; r < 4; r++)
	{
		lcd->SetRotation(r);

		lcd->Clear(LCD_COLOR_WHITE);

		lcd->SetTextColor(lcd_colors[r]);

		uint16_t r1 = 10;
		uint16_t r2 = 20;

		uint16_t w = lcd->GetWidth();
		uint16_t h = lcd->GetHeight();

		for (uint16_t x = 0; x <= w; x += r2)
		{
			for (uint16_t y = 0; y <= h; y += r2)
			{
				lcd->FillCircle(x, y, r1);
			}
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Main::demoChar()
{
	lcd->Clear(LCD_COLOR_WHITE);

	lcd->SetTextColor(LCD_COLOR_RED);

	lcd->SetFont(&Font24);

	for (uint8_t r = 0; r < 4; r++)
	{
		lcd->SetRotation(r);

		lcd->DisplayChar(10, 10, 'F');

		lcd->DisplayStringAt(10, 35, (uint8_t*) "ILI9325", CENTER_MODE);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Main::demoImage()
{
	for (uint8_t r = 0; r < 4; r++)
	{
		lcd->SetRotation(r);

		lcd->DrawRGBImage(0, 0, 240, 180, (uint16_t*)stm32_mini_map);

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void Main::demoArc()
{
	lcd->Clear(LCD_COLOR_WHITE);

	const uint8_t SECTORS = 20;

	/** The ANGLE sector. */
	const float ANGLE_SECTOR = 360.0 / SECTORS;

	/** The ANGLE start. */
	const float ANGLE_START = 0 - ANGLE_SECTOR / 2;

	// ============================<
	// Define sizes of board's figures
	// ================================>
	const uint16_t centerX = 120;
	const uint16_t centerY = 120;

	const float widthNarrowZone = 240 / SECTORS;
	const float widthWideZone = widthNarrowZone * 2;

	// ==============<
	// Make MISS-sectors
	// ==================>
	float angleStartZone = ANGLE_START;
	float angleEndZone = ANGLE_START + ANGLE_SECTOR;
	float outerRadiusZone = 3 * widthWideZone + 4 * widthNarrowZone;
	float innerRadiusZone = outerRadiusZone - widthWideZone;

	lcd->SetTextColor(LCD_COLOR_BLACK);

	for (uint8_t i = 0; i < SECTORS; i++)
	{
		lcd->FillArc(centerX, centerY, outerRadiusZone, innerRadiusZone, angleStartZone, angleEndZone);

		angleStartZone = angleEndZone;
		angleEndZone += ANGLE_SECTOR;
	}
	//=================<
	// Make DOUBLE-sectors
	// ====================>
	angleStartZone = ANGLE_START;
	angleEndZone = ANGLE_START + ANGLE_SECTOR;
	innerRadiusZone -= widthNarrowZone;
	outerRadiusZone -= widthWideZone;

	for (uint8_t i = 0; i < SECTORS; i++)
	{
		lcd->SetTextColor((i % 2 == 0) ? LCD_COLOR_GREEN : LCD_COLOR_RED);

		lcd->FillArc(centerX, centerY, outerRadiusZone, innerRadiusZone, angleStartZone, angleEndZone);

		angleStartZone = angleEndZone;
		angleEndZone += ANGLE_SECTOR;
	}

	// ====================<
	// Make top SINGLE-sectors
	// ========================>
	angleStartZone = ANGLE_START;
	angleEndZone = ANGLE_START + ANGLE_SECTOR;
	innerRadiusZone -= widthWideZone;
	outerRadiusZone -= widthNarrowZone;

	for (uint8_t i = 0; i < SECTORS; i++)
	{
		lcd->SetTextColor((i % 2 == 0) ? LCD_COLOR_BLACK : LCD_COLOR_WHITE);

		lcd->FillArc(centerX, centerY, outerRadiusZone, innerRadiusZone, angleStartZone, angleEndZone);

		angleStartZone = angleEndZone;
		angleEndZone += ANGLE_SECTOR;
	}
	// ================<
	// Make TRIPLE-sectors
	// ====================>
	angleStartZone = ANGLE_START;
	angleEndZone = ANGLE_START + ANGLE_SECTOR;
	innerRadiusZone -= widthNarrowZone;
	outerRadiusZone -= widthWideZone;

	for (uint8_t i = 0; i < SECTORS; i++)
	{
		lcd->SetTextColor((i % 2 == 0) ? LCD_COLOR_GREEN : LCD_COLOR_RED);

		lcd->FillArc(centerX, centerY, outerRadiusZone, innerRadiusZone, angleStartZone, angleEndZone);

		angleStartZone = angleEndZone;
		angleEndZone += ANGLE_SECTOR;
	}
	// =======================<
	// Make bottom SINGLE-sectors
	// ===========================>
	angleStartZone = ANGLE_START;
	angleEndZone = ANGLE_START + ANGLE_SECTOR;
	innerRadiusZone -= widthWideZone;
	outerRadiusZone -= widthNarrowZone;

	for (uint8_t i = 0; i < SECTORS; i++)
	{
		lcd->SetTextColor((i % 2 == 0) ? LCD_COLOR_BLACK : LCD_COLOR_WHITE);

		lcd->FillArc(centerX, centerY, outerRadiusZone, innerRadiusZone, angleStartZone, angleEndZone);

		angleStartZone = angleEndZone;
		angleEndZone += ANGLE_SECTOR;
	}
	// ===============<
	// Make RING and BULL
	// ===================>
	innerRadiusZone -= widthNarrowZone;
	outerRadiusZone -= widthWideZone;

	lcd->SetTextColor(LCD_COLOR_GREEN);

	lcd->FillArc(centerX, centerY, outerRadiusZone, innerRadiusZone, 0, 360);

	innerRadiusZone = 0;
	outerRadiusZone -= widthNarrowZone;

	lcd->SetTextColor(LCD_COLOR_RED);

	lcd->FillArc(centerX, centerY, outerRadiusZone, innerRadiusZone, 0, 360);

}

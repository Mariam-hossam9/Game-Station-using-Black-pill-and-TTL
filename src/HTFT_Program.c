/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : HTFT_Program.c                                                          */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* This file provides the driver implementation for the TFT display module             */
/* (based on SPI communication) using the STM32 (Black Pill) microcontroller.          */
/*                                                                                     */
/* Features:                                                                           */
/*   - Initializes TFT control and reset pins.                                         */
/*   - Performs reset sequence and sleep-out command.                                  */
/*   - Configures display color mode (RGB565).                                         */
/*   - Provides APIs to:                                                               */
/*       * Initialize the display.                                                     */
/*       * Send commands and data to TFT.                                              */
/*       * Display images from a buffer.                                               */
/*       * Clear or fill the screen with color.                                        */
/*       * Print text using a 5x7 font.                                                */
/*                                                                                     */
/* Usage:                                                                              */
/*   1. Call `HTFT_voidInit()` before using display functions.                         */
/*   2. Use `HTFT_voidDisplay()` to draw an image buffer on the TFT.                   */
/*   3. Call `HTFT_voidFillColor(color)` to fill the entire screen.                    */
/*   4. Use `HTFT_voidPrintText(str, x, y, fg, bg)` to draw text.                      */
/***************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_Interface.h"
#include "MSTK_Interface.h"
#include "MSPI_Interface.h"

#include "HTFT_Interface.h"
#include "HTFT_Private.h"
#include "HTFT_Config.h"

void HTFT_voidInit()
{
    // Configure Control pin & Reset pin
    MGPIO_voidSetMode(TFT_PORT, CONTROL_PIN, OUTPUT);
    MGPIO_voidSetOutputConfig(TFT_PORT, CONTROL_PIN, Push_Pull, Low_Speed);
    MGPIO_voidSetMode(TFT_PORT, RST_PIN, OUTPUT);
    MGPIO_voidSetOutputConfig(TFT_PORT, RST_PIN, Push_Pull, Low_Speed);

    // Reset Sequence
    MGPIO_voidSetPinValue(TFT_PORT, RST_PIN, HIGH);
    MSTK_voidDelayus(100);
    MGPIO_voidSetPinValue(TFT_PORT, RST_PIN, LOW);
    MSTK_voidDelayus(1);
    MGPIO_voidSetPinValue(TFT_PORT, RST_PIN, HIGH);
    MSTK_voidDelayus(100);
    MGPIO_voidSetPinValue(TFT_PORT, RST_PIN, LOW);
    MSTK_voidDelayus(100);
    MGPIO_voidSetPinValue(TFT_PORT, RST_PIN, HIGH);
    MSTK_voidDelayms(120);

    // Sleep out
    HTFT_voidWriteCommand(SLEEP_OUT);
    MSTK_voidDelayms(10);

    // Select Color mode
    HTFT_voidWriteCommand(COLOR_MODE);
    HTFT_voidWriteData(RGB565);

    // Display on
    HTFT_voidWriteCommand(DISPLAY_ON);
}

static void HTFT_voidWriteData(u8 Copy_u8Data)
{
    MGPIO_voidSetPinValue(TFT_PORT, CONTROL_PIN, HIGH);
    (void)MSPI_u16Tranceive(Copy_u8Data);
}

static void HTFT_voidWriteCommand(u8 Copy_u8CMD)
{
    MGPIO_voidSetPinValue(TFT_PORT, CONTROL_PIN, LOW);
    (void)MSPI_u16Tranceive(Copy_u8CMD);
}

void HTFT_voidDisplay(const u16* Copy_pu16PTR)
{
    u16 Local_u16Iterator;
    u8 Local_u8HighPart, Local_u8LowPart;

    // Set x
    HTFT_voidWriteCommand(X_DIRECTION);
    HTFT_voidWriteData(START_X_B0);
    HTFT_voidWriteData(START_X_B1);
    HTFT_voidWriteData(END_X_B0);
    HTFT_voidWriteData(END_X_B1);

    // Set Y
    HTFT_voidWriteCommand(Y_DIRECTION);
    HTFT_voidWriteData(START_Y_B0);
    HTFT_voidWriteData(START_Y_B1);
    HTFT_voidWriteData(END_Y_B0);
    HTFT_voidWriteData(END_Y_B1);

    // Write on the screen
    HTFT_voidWriteCommand(SCREEN_WRITE);

    for(Local_u16Iterator=0; Local_u16Iterator<IMAGE_SIZE; Local_u16Iterator++)
    {
        Local_u8LowPart  = (u8)Copy_pu16PTR[Local_u16Iterator];       // lsb
        Local_u8HighPart = (u8)(Copy_pu16PTR[Local_u16Iterator]>>8);  // msb

        HTFT_voidWriteData(Local_u8HighPart);
        HTFT_voidWriteData(Local_u8LowPart);
    }
}

/* ===========================================================
   NEW FUNCTIONS ADDED
   =========================================================== */

// Fill entire screen with one color
void HTFT_voidFillColor(u16 color)
{
    u32 i;
    u8 high = color >> 8;
    u8 low  = color & 0xFF;

    // Set full screen area
    HTFT_voidWriteCommand(X_DIRECTION);
    HTFT_voidWriteData(START_X_B0);
    HTFT_voidWriteData(START_X_B1);
    HTFT_voidWriteData(END_X_B0);
    HTFT_voidWriteData(END_X_B1);

    HTFT_voidWriteCommand(Y_DIRECTION);
    HTFT_voidWriteData(START_Y_B0);
    HTFT_voidWriteData(START_Y_B1);
    HTFT_voidWriteData(END_Y_B0);
    HTFT_voidWriteData(END_Y_B1);

    HTFT_voidWriteCommand(SCREEN_WRITE);

    for(i=0; i<IMAGE_SIZE; i++)
    {
        HTFT_voidWriteData(high);
        HTFT_voidWriteData(low);
    }
}

// --- Simple 5x7 font for text ---
static const u8 font5x7[][5] = {
	{0x00,0x00,0x00,0x00,0x00}, // space
	// '0'
	{0x3E,0x45,0x49,0x51,0x3E},
	// '1'
	{0x00,0x42,0x7F,0x40,0x00},
	// '2'
	{0x42,0x61,0x51,0x49,0x46},
	// '3'
	{0x21,0x41,0x45,0x4B,0x31},
	// '4'
	{0x18,0x14,0x12,0x7F,0x10},
	// '5'
	{0x27,0x45,0x45,0x45,0x39},
	// '6'
	{0x3C,0x4A,0x49,0x49,0x30},
	// '7'
	{0x01,0x71,0x09,0x05,0x03},
	// '8'
	{0x36,0x49,0x49,0x49,0x36},
	// '9'
	{0x06,0x49,0x49,0x29,0x1E},
    // 'Y' (ASCII 89)
    {0x04,0x08,0x70,0x08,0x04},
    // 'O' (ASCII 79)
    {0x3E,0x41,0x41,0x41,0x3E},
    // 'U' (ASCII 85)
    {0x3F,0x40,0x40,0x40,0x3F},
    // 'S' (ASCII 83)
    {0x22,0x49,0x49,0x49,0x31},
    // 'C' (ASCII 67)
    {0x3E,0x41,0x41,0x41,0x22},
    // 'R' (ASCII 82)
    {0x7F,0x09,0x19,0x29,0x46},
    // 'E' (ASCII 69)
    {0x7F,0x49,0x49,0x49,0x41},
    // '=' (ASCII 61)
    {0x14,0x14,0x14,0x14,0x14}
};


void HTFT_voidPrintText(char *str, u16 x, u16 y, u16 textColor, u16 bgColor)
{
    u8 highText = textColor >> 8;
    u8 lowText  = textColor & 0xFF;
    u8 highBg   = bgColor >> 8;
    u8 lowBg    = bgColor & 0xFF;
    // Calculate string length
    int len = 0;
    char *temp = str;
    while(*temp++) len++;
    // Calculate total text width and center it on 128px wide screen
    u16 textWidth = len * 8; // Each character is 6 pixels wide (5 + 1 spacing)
    u16 centerX = 64 - (textWidth / 2); // Center on 128px screen (128/2 = 64)
    // Start from the end of the string and work backwards
    for(int i = len - 1; i >= 0; i--)
    {
        char c = str[i];
        const u8 *bitmap;
        // Map character to font index
        if(c >= '0' && c <= '9') bitmap = font5x7[c - '0' + 1];
        else if(c == 'Y') bitmap = font5x7[11];
        else if(c == 'O') bitmap = font5x7[12];
        else if(c == 'U') bitmap = font5x7[13];
        else if(c == 'S') bitmap = font5x7[14];
        else if(c == 'C') bitmap = font5x7[15];
        else if(c == 'R') bitmap = font5x7[16];
        else if(c == 'E') bitmap = font5x7[17];
        else if(c == '=') bitmap = font5x7[18];
        else bitmap = font5x7[0]; // space
        // Draw character rotated 180° (flip both horizontally and vertically)
        for(int row = 6; row >= 0; row--) // vertical flip
        {
            u16 py = y + (6 - row); // adjust y
            for(int col = 4; col >= 0; col--) // horizontal flip
            {
                u16 px = centerX + (4 - col); // use centered x position
                HTFT_voidWriteCommand(X_DIRECTION);
                HTFT_voidWriteData((px >> 8) & 0xFF);
                HTFT_voidWriteData(px & 0xFF);
                HTFT_voidWriteData((px >> 8) & 0xFF);
                HTFT_voidWriteData(px & 0xFF);
                HTFT_voidWriteCommand(Y_DIRECTION);
                HTFT_voidWriteData((py >> 8) & 0xFF);
                HTFT_voidWriteData(py & 0xFF);
                HTFT_voidWriteData((py >> 8) & 0xFF);
                HTFT_voidWriteData(py & 0xFF);
                HTFT_voidWriteCommand(SCREEN_WRITE);
                if(bitmap[col] & (1 << row))
                {
                    HTFT_voidWriteData(highText);
                    HTFT_voidWriteData(lowText);
                }
                else
                {
                    HTFT_voidWriteData(highBg);
                    HTFT_voidWriteData(lowBg);
                }
            }
        }
        centerX += 6; // Move to next character position
    }
}

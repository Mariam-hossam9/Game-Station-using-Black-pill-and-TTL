/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MATHQUIZ_Program.c                                                      */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* This file implements the Math Quiz game logic using TFT display and STM32 MCU.      */
/*                                                                                     */
/* Features:                                                                           */
/*   - Initializes RCC, GPIO, SPI, SysTick, and TFT modules.                           */
/*   - Displays a sequence of quiz images and waits for user input via buttons.        */
/*   - Tracks correct answers and displays the final score.                            */
/*                                                                                     */
/* Usage:                                                                              */
/*   1. Call `MATHQUIZ_voidInit()` to initialize all peripherals.                      */
/*   2. Call `MATHQUIZ_voidRunSequence()` to start the quiz game.                      */
/***************************************************************************************/

#include <stdio.h>
#include "STD_TYPES.h"
#include "MRCC_Interface.h"
#include "MGPIO_Interface.h"
#include "MSTK_Interface.h"
#include "MSPI_Interface.h"
#include "HTFT_Interface.h"
#include "MATHQUIZ_Interface.h"
#include "TFT_Image2.h"
#include "TFT_Image3.h"
#include "TFT_Image4.h"
#include "TFT_Image5.h"
#include "TFT_Image6.h"
#include "TFT_Image7.h"

extern const u16 Image3_ARR[];

// Button Pins on PORTA
#define BTN1   PIN2  // PA8
#define BTN2   PIN3  // PA9
#define BTN3   PIN4  // PA10

// ------------------------------------------------------------
// Initialize peripherals
// ------------------------------------------------------------
void MATHQUIZ_voidInit(void)
{
    //MRCC_voidInit();

    // Enable GPIOA + SPI1 clocks
    MRCC_voidEnablePeripheralClock(AHB1_BUS, AHB1_GPIOA);
    MRCC_voidEnablePeripheralClock(APB2_BUS, APB2_SPI1);

    // Configure SPI pins
    MGPIO_voidSetMode(PORTA, PIN4, Alternative_Func);
    MGPIO_voidSetAlternativeConfig(PORTA, PIN4, AF5);

    MGPIO_voidSetMode(PORTA, PIN5, Alternative_Func);
    MGPIO_voidSetAlternativeConfig(PORTA, PIN5, AF5);

    MGPIO_voidSetMode(PORTA, PIN6, Alternative_Func);
    MGPIO_voidSetAlternativeConfig(PORTA, PIN6, AF5);

    MGPIO_voidSetMode(PORTA, PIN7, Alternative_Func);
    MGPIO_voidSetAlternativeConfig(PORTA, PIN7, AF5);

    // Configure buttons
    MGPIO_voidSetMode(PORTA, BTN1, INPUT);
    MGPIO_voidSetInputConfig(PORTA, BTN1, PULLUP);

    MGPIO_voidSetMode(PORTA, BTN2, INPUT);
    MGPIO_voidSetInputConfig(PORTA, BTN2, PULLUP);

    MGPIO_voidSetMode(PORTA, BTN3, INPUT);
    MGPIO_voidSetInputConfig(PORTA, BTN3, PULLUP);

    // Init SysTick, SPI, TFT
    MSTK_voidInit();
    MSPI_voidMasterInit();
    HTFT_voidInit();
}

// ------------------------------------------------------------
// Run the sequence of quiz images
// ------------------------------------------------------------
void MATHQUIZ_voidRunSequence(void)
{
    u8 pressed = 0;
    u8 score = 0; // 🔹 counts how many times Image3 appears

    // Step 1
    HTFT_voidDisplay(Image7_ARR);
    MSTK_voidDelayms(2000);

    // Step 2
    HTFT_voidDisplay(Image2_ARR);

    pressed = 0;
    while(!pressed)
    {
        if (rx_data == 'Q')
        			break;
        if(MGPIO_u8GetPinValue(PORTA, BTN2) == 0)
        {
            MSTK_voidDelayms(50);
            if(MGPIO_u8GetPinValue(PORTA, BTN2) == 0)
            {
                while(MGPIO_u8GetPinValue(PORTA, BTN2) == 0);
                HTFT_voidDisplay(Image3_ARR);
                score++;  // 🔹 increase score
                pressed = 1;
            }
        }
        else if(MGPIO_u8GetPinValue(PORTA, BTN1) == 0 || MGPIO_u8GetPinValue(PORTA, BTN3) == 0)
        {
            MSTK_voidDelayms(50);
            if(MGPIO_u8GetPinValue(PORTA, BTN1) == 0 || MGPIO_u8GetPinValue(PORTA, BTN3) == 0)
            {
                while(MGPIO_u8GetPinValue(PORTA, BTN1) == 0 || MGPIO_u8GetPinValue(PORTA, BTN3) == 0);
                HTFT_voidDisplay(Image4_ARR);
                pressed = 1;
            }
        }
    }

    // Step 3
    MSTK_voidDelayms(2000);
    HTFT_voidDisplay(Image5_ARR);

    pressed = 0;
    while(!pressed)
    {
        if (rx_data == 'Q')
        			break;
        if(MGPIO_u8GetPinValue(PORTA, BTN1) == 0)
        {
            MSTK_voidDelayms(50);
            if(MGPIO_u8GetPinValue(PORTA, BTN1) == 0)
            {
                while(MGPIO_u8GetPinValue(PORTA, BTN1) == 0);
                HTFT_voidDisplay(Image3_ARR);
                score++;  // 🔹 increase score
                pressed = 1;
            }
        }
        else if(MGPIO_u8GetPinValue(PORTA, BTN2) == 0 || MGPIO_u8GetPinValue(PORTA, BTN3) == 0)
        {
            MSTK_voidDelayms(50);
            if(MGPIO_u8GetPinValue(PORTA, BTN2) == 0 || MGPIO_u8GetPinValue(PORTA, BTN3) == 0)
            {
                while(MGPIO_u8GetPinValue(PORTA, BTN2) == 0 || MGPIO_u8GetPinValue(PORTA, BTN3) == 0);
                HTFT_voidDisplay(Image4_ARR);
                pressed = 1;
            }
        }
    }

    // Step 4
    MSTK_voidDelayms(2000);
    HTFT_voidDisplay(Image6_ARR);

    pressed = 0;
    while(!pressed)
    {
        if (rx_data == 'Q')
        			break;
        if(MGPIO_u8GetPinValue(PORTA, BTN3) == 0)
        {
            MSTK_voidDelayms(50);
            if(MGPIO_u8GetPinValue(PORTA, BTN3) == 0)
            {
                while(MGPIO_u8GetPinValue(PORTA, BTN3) == 0);
                HTFT_voidDisplay(Image3_ARR);
                score++;  // 🔹 increase score
                pressed = 1;
            }
        }
        else if(MGPIO_u8GetPinValue(PORTA, BTN2) == 0 || MGPIO_u8GetPinValue(PORTA, BTN1) == 0)
        {
            MSTK_voidDelayms(50);
            if(MGPIO_u8GetPinValue(PORTA, BTN2) == 0 || MGPIO_u8GetPinValue(PORTA, BTN1) == 0)
            {
                while(MGPIO_u8GetPinValue(PORTA, BTN2) == 0 || MGPIO_u8GetPinValue(PORTA, BTN1) == 0);
                HTFT_voidDisplay(Image4_ARR);
                pressed = 1;
            }
        }
    }

    // ---------- Show Final Score ----------
    MSTK_voidDelayms(2000);
    HTFT_voidFillColor(0xFFFF); // clear screen white

    char msg[20];
    sprintf(msg, "YOUR SCORE= %d", score);
    HTFT_voidPrintText(msg, 20, 70, 0x0000, 0xFFFF); // black text on white

    //while(1); // stay here
}

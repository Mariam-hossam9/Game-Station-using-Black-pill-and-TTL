/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : LEDMEMORY_Program.c                                                     */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* This file implements the LED Memory Game logic using STM32 and TFT display.         */
/* Players must repeat an increasing sequence of LED flashes using button inputs.      */
/*                                                                                     */
/* Features:                                                                           */
/*   - Generates and displays random LED sequences.                                   */
/*   - Reads player inputs through buttons.                                           */
/*   - Shows results and score on the TFT screen.                                     */
/*   - Integrates visual feedback with TFT images.                                    */
/*                                                                                     */
/* Usage:                                                                              */
/*   1. Call `Game_Init()` to configure peripherals (RCC, GPIO, SPI, TFT, etc.).       */
/*   2. Call `Game_Run()` to start the LED memory sequence game.                       */
/***************************************************************************************/

#include "LEDMEMORY_Interface.h"
#include "MRCC_Interface.h"
#include "MGPIO_Interface.h"
#include "MSTK_Interface.h"
#include "MSPI_Interface.h"
#include "HTFT_Interface.h"
#include "TFT_Image7.h"
#include "TFT_Image3.h"
#include "TFT_Image4.h"

#include <stdlib.h>
#include <stdio.h>

// Store the sequence of LEDs (0,1,2)
static u8 sequence[MAX_SEQUENCE_LENGTH];
static u8 sequence_length = 1;
static u8 score = 0;

// ---------- Helper Functions ----------
static void delay_ms(u32 ms)
{
    MSTK_voidDelayms(ms);
}

static void LED_On(u8 led)
{
    switch(led)
    {
        case 0: MGPIO_voidSetPinValue(LED_PORT, LED_PIN0, HIGH); break;
        case 1: MGPIO_voidSetPinValue(LED_PORT, LED_PIN1, HIGH); break;
        case 2: MGPIO_voidSetPinValue(LED_PORT, LED_PIN2, HIGH); break;
    }
}

static void LED_Off(u8 led)
{
    switch(led)
    {
        case 0: MGPIO_voidSetPinValue(LED_PORT, LED_PIN0, LOW); break;
        case 1: MGPIO_voidSetPinValue(LED_PORT, LED_PIN1, LOW); break;
        case 2: MGPIO_voidSetPinValue(LED_PORT, LED_PIN2, LOW); break;
    }
}

static void LEDs_OffAll(void)
{
    LED_Off(0);
    LED_Off(1);
    LED_Off(2);
}

static void PlaySequence(void)
{
    for(u8 i = 0; i < sequence_length; i++)
    {
        LED_On(sequence[i]);
        delay_ms(500);
        LED_Off(sequence[i]);
        delay_ms(250);
    }
}

static u8 ReadButton(void)
{
    if(MGPIO_u8GetPinValue(BTN_PORT, BTN_PIN0) == LOW) return 0;
    if(MGPIO_u8GetPinValue(BTN_PORT, BTN_PIN1) == LOW) return 1;
    if(MGPIO_u8GetPinValue(BTN_PORT, BTN_PIN2) == LOW) return 2;
    return 255; // no button pressed
}

static u8 GetUser_Input(void)
{
    u8 btn;
    while(1)
    {
        btn = ReadButton();
        if(btn != 255)
        {
            while(ReadButton() != 255); // Wait for release
            delay_ms(50);
            return btn;
        }
    }
}


// ---------- Public Functions ----------
void Game_Init(void)
{
    // Init RCC
    //MRCC_voidInit();
    MRCC_voidEnablePeripheralClock(AHB1_BUS, AHB1_GPIOA);
    MRCC_voidEnablePeripheralClock(AHB1_BUS, AHB1_GPIOB);
    MRCC_voidEnablePeripheralClock(APB2_BUS, APB2_SPI1);

    // Configure SPI pins for TFT
        MGPIO_voidSetMode(PORTA, PIN4, Alternative_Func);
        MGPIO_voidSetAlternativeConfig(PORTA, PIN4, AF5);
        MGPIO_voidSetMode(PORTA, PIN5, Alternative_Func);
        MGPIO_voidSetAlternativeConfig(PORTA, PIN5, AF5);
        MGPIO_voidSetMode(PORTA, PIN6, Alternative_Func);
        MGPIO_voidSetAlternativeConfig(PORTA, PIN6, AF5);
        MGPIO_voidSetMode(PORTA, PIN7, Alternative_Func);
        MGPIO_voidSetAlternativeConfig(PORTA, PIN7, AF5);

    // SysTick
    MSTK_voidInit();

    // SPI + TFT
    MSPI_voidMasterInit();
    HTFT_voidInit();

    // LED pins
    MGPIO_voidSetMode(LED_PORT, LED_PIN0, OUTPUT);
    MGPIO_voidSetOutputConfig(LED_PORT, LED_PIN0, Push_Pull, VHigh_Speed);
    MGPIO_voidSetMode(LED_PORT, LED_PIN1, OUTPUT);
    MGPIO_voidSetOutputConfig(LED_PORT, LED_PIN1, Push_Pull, VHigh_Speed);
    MGPIO_voidSetMode(LED_PORT, LED_PIN2, OUTPUT);
    MGPIO_voidSetOutputConfig(LED_PORT, LED_PIN2, Push_Pull, VHigh_Speed);

    // Buttons
    MGPIO_voidSetMode(BTN_PORT, BTN_PIN0, INPUT);
    MGPIO_voidSetInputConfig(BTN_PORT, BTN_PIN0, PULLUP);
    MGPIO_voidSetMode(BTN_PORT, BTN_PIN1, INPUT);
    MGPIO_voidSetInputConfig(BTN_PORT, BTN_PIN1, PULLUP);
    MGPIO_voidSetMode(BTN_PORT, BTN_PIN2, INPUT);
    MGPIO_voidSetInputConfig(BTN_PORT, BTN_PIN2, PULLUP);

    // TFT Start Screen
    HTFT_voidDisplay(Image7_ARR);
    MSTK_voidDelayms(2000);

    // Seed random generator
    //srand(1234);
    srand(MSTK_u32GetCurrentValue());
}


void Game_Run(void)
{
    u8 game_over = 0;

    while(!game_over)
    {
        if (rx_data == 'Q')
        			break;
        // Generate random sequence
        for(u8 i = 0; i < sequence_length; i++)
            sequence[i] = rand() % 3;

        // Play sequence
        PlaySequence();

        // Check user input
        u8 failed = 0;
        for(u8 i = 0; i < sequence_length; i++)
        {
            u8 input = GetUser_Input();
            if(input != sequence[i])
            {
                failed = 1;
                break;
            }
        }

        if(failed)
        {
            HTFT_voidDisplay(Image4_ARR);
            LEDs_OffAll();
            MSTK_voidDelayms(2000);
            HTFT_voidFillColor(0xFFFF);
            char msg[20];
            sprintf(msg, "YOUR SCORE= %d", score);
            HTFT_voidPrintText(msg, 20, 70, 0x0000, 0xFFFF);

            game_over = 1;  // Stop the game
        }
        else
        {
            score++;
            HTFT_voidDisplay(Image3_ARR);
            MSTK_voidDelayms(1000);
            if(sequence_length < MAX_SEQUENCE_LENGTH)
                sequence_length++;
        }
    }

    // Reset variables for next time
    sequence_length = 1;
    score = 0;

}

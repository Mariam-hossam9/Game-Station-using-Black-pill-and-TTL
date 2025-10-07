/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : main.c                                                                  */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* This is the main application entry point for the STM32 project integrating           */
/* multiple mini-games and modules via USART commands.                                 */
/*                                                                                     */
/* Features:                                                                           */
/*   - Initializes MCU peripherals (RCC, GPIO, SPI, USART, SysTick).                   */
/*   - Waits for serial input to select and run a specific module:                     */
/*       * 'L' → LED Memory Game                                                       */
/*       * 'M' → Math Quiz Game                                                        */
/*       * 'S' → Snake Game                                                            */
/*   - Uses USART interrupt handling for input reception.                              */
/*                                                                                     */
/* Usage:                                                                              */
/*   1. Upload all drivers and this main file to the STM32 environment.                */
/*   2. Open a serial terminal and send 'L', 'M', or 'S' to start a module.            */
/***************************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "MRCC_Interface.h"
#include "MSTK_Interface.h"
#include "MGPIO_Interface.h"
#include "MSPI_Interface.h"
#include "MNVIC_Interface.h"
#include "MEXTI_Interface.h"
#include "MUSART_Interface.h"

#include "HTFT_Interface.h"
#include "HSTP_Interface.h"
#include "HLEDMATRIX_Interface.h"
#include "MATHQUIZ_Interface.h"
#include "LEDMEMORY_Interface.h"
#include "snake.h"

volatile u8 quit_flag;
u8 rx_data;
void USART1_IRQHandler(void);

int main(void)
{
    // ---------- Init System ----------
    MRCC_voidInit();

    // Enable clocks
    MRCC_voidEnablePeripheralClock(AHB1_BUS, AHB1_GPIOA);
    MRCC_voidEnablePeripheralClock(AHB1_BUS, AHB1_GPIOB);
    MRCC_voidEnablePeripheralClock(APB2_BUS, APB2_USART1);   // USART1
    MRCC_voidEnablePeripheralClock(APB2_BUS, APB2_SPI1);

    // Configure USART pins: PA9 (TX), PA10 (RX)
    MGPIO_voidSetMode(PORTA, PIN9, Alternative_Func);
    MGPIO_voidSetAlternativeConfig(PORTA, PIN9, AF7);
    MGPIO_voidSetMode(PORTA, PIN10, Alternative_Func);
    MGPIO_voidSetAlternativeConfig(PORTA, PIN10, AF7);

    // Init USART1
    MUSART_voidInit();
    MSPI_voidMasterInit();

    // ---------- Wait for Command ----------
    while(1)
    {


        // Blocking receive (wait until a byte arrives)
        rx_data = MUSART_u8RecieveData();

        if(rx_data == 'L')       // Start LED Memory Game
        {
            Game_Init();
            Game_Run();         // Make sure this returns when game finishes
        }
        else if(rx_data == 'M')  // Start Math Quiz
        {
            MATHQUIZ_voidInit();
            MATHQUIZ_voidRunSequence();  // Make sure this returns when quiz finishes
        }
        else if (rx_data == 'S')
        {
        	Snake_RunGame();
        }
        // After finishing a game or quiz, loop back to wait for new command
    }
}




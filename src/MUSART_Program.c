/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MUSART_Program.c                                                        */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* Universal Synchronous/Asynchronous Receiver/Transmitter (USART) driver for STM32.   */
/* Provides initialization, send/receive functions, and interrupt handling.            */
/*                                                                                     */
/* Features:                                                                           */
/*   - Configures baud rate, word length, and parity.                                  */
/*   - Supports blocking send and receive functions.                                   */
/*   - Handles strings transmission and reception.                                     */
/*   - Includes USART1 interrupt handler for data reception.                           */
/*                                                                                     */
/* Usage:                                                                              */
/*   1. Call `MUSART_voidInit()` to initialize USART peripheral.                       */
/*   2. Use `MUSART_voidSendData()` and `MUSART_u8RecieveData()` for data transfer.    */
/*   3. Optionally enable interrupt handler `USART1_IRQHandler()` for asynchronous I/O.*/
/***************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MUSART_Interface.h"
#include "MUSART_Private.h"
#include "MNVIC_Interface.h"


void MUSART_voidInit(void)
{
    //oversampling = 16
    USART1 -> CR1.OVER8 = 0;
    //buadrate =9600
    USART1 -> BRR = ((104 <<4)+3);
    //wordlength = 8 bit
    USART1 -> CR1.M = 0;
    //Disable parity
    USART1 -> CR1.PCE = 0;
    //enable transmitter
    USART1 -> CR1.TE = 1;
    //enable Reciever
    USART1 -> CR1.RE = 1;
    //enable Uart
    USART1 -> CR1.UE = 1;
}

void MUSART_voidSendData(u8 Copy_u8Data)
{
	while (!(USART1->SR & (1 << 7)));   // Wait until TXE=1
    USART1->DR = Copy_u8Data;
}
u8 MUSART_u8RecieveData(void)
{
    while (!(USART1->SR & (1 << 5)));  // Wait until RXNE=1
    return (u8)(USART1->DR & 0xFF);
}

void MUSART_voidSendString(u8 *Copy_pu8Str)
{
    while (*Copy_pu8Str != '\0')   // Loop until end of string
    {
        MUSART_voidSendData(*Copy_pu8Str);
        Copy_pu8Str++;
    }
}

void MUSART_voidRecieveString(u8 *Copy_pu8Str)
{
    u8 i = 0;
    u8 data;

    do {
        data = MUSART_u8RecieveData();
        Copy_pu8Str[i++] = data;
    } while (data != '\n');   // stop when newline is received

    Copy_pu8Str[i] = '\0';   // null-terminate string
}
void USART1_IRQHandler(void)
{
    if (USART1->SR & (1 << RXNE))  // Check RXNE bit
    {
        char c = (char)(USART1->DR & 0xFF);  // Read data (clears RXNE)
        if (c == 'Q' || c == 'q')
        {
            quit_flag = 1;
        }
    }
}



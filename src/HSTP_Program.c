/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : HSTP_Program.c                                                          */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* This file provides the driver implementation for controlling a serial-in,           */
/* parallel-out shift register (e.g., 74HC595) using GPIO and SPI-like timing.         */
/*                                                                                     */
/* Features:                                                                           */
/*   - Initializes shift, latch, and serial data pins.                                 */
/*   - Sends serial data bit-by-bit to the shift register.                             */
/*   - Provides control to latch and output data to connected peripherals.              */
/*                                                                                     */
/* Usage:                                                                              */
/*   1. Call `HSTP_voidInit()` to configure shift register pins.                       */
/*   2. Use `HSTP_voidShiftData(byte)` to send 8-bit data serially.                    */
/*   3. Call `HSTP_voidSendData()` to latch and output the shifted data.               */
/***************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_interface.h"
#include "MSTK_Interface.h"
#include "HSTP_Interface.h"


void HSTP_voidInit()
{
	//Serial Data Input(PORTA,PIN0,OUTPUT)
	MGPIO_voidSetMode(HSTP_PORT,SDI,OUTPUT);
	MGPIO_voidSetOutputConfig(HSTP_PORT,SDI,Push_Pull,Low_Speed);
	
	//Shift Regsiter(PORTA,PIN0,OUTPUT)
	MGPIO_voidSetMode(HSTP_PORT,SHIFT,OUTPUT);
	MGPIO_voidSetOutputConfig(HSTP_PORT,SHIFT,Push_Pull,Low_Speed);
	
	//Latch Register(PORTA,PIN0,OUTPUT)
	MGPIO_voidSetMode(HSTP_PORT,LATCH,OUTPUT);
	MGPIO_voidSetOutputConfig(HSTP_PORT,LATCH,Push_Pull,Low_Speed);
}
void HSTP_voidShiftData(u8 Copy_u8Data)
{
	s8 Local_u8Iterator=0;
	for(Local_u8Iterator=7;Local_u8Iterator>=0;Local_u8Iterator--)
	{
		MGPIO_voidSetPinValue(HSTP_PORT,SDI,((Copy_u8Data>>Local_u8Iterator)&0x01));
		MGPIO_voidSetPinValue(HSTP_PORT,SHIFT,LOW);
		MSTK_voidDelayms(10);
		MGPIO_voidSetPinValue(HSTP_PORT,SHIFT,HIGH);
	}
}
void HSTP_voidSendData()
{
	MGPIO_voidSetPinValue(HSTP_PORT,LATCH,LOW);
	MSTK_voidDelayms(10);
	MGPIO_voidSetPinValue(HSTP_PORT,LATCH,HIGH);
}



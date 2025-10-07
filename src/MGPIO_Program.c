/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MGPIO_Program.c                                                         */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* General Purpose I/O (GPIO) driver for STM32 microcontrollers.                       */
/* Provides APIs for pin configuration, read/write operations, and alternate functions.*/
/*                                                                                     */
/* Features:                                                                           */
/*   - Configures pin mode, type, speed, and pull-up/down.                             */
/*   - Supports atomic set/reset operations.                                           */
/*   - Reads pin input values.                                                         */
/*   - Configures alternate functions for peripherals.                                 */
/***************************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "MGPIO_Interface.h"
#include "MGPIO_Private.h"
#include "MGPIO_Config.h"

void MGPIO_voidSetMode(Port_t Copy_uddtPort,PIN_t Copy_uddtPin,Modes_t Copy_uddtMode)
{
	if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		
	}
	else
	{
		switch(Copy_uddtPort)
		{
			case PORTA:
			GPIOA->MODER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOA->MODER|=(Copy_uddtMode<<(Copy_uddtPin*2));
			break;
			case PORTB:
			GPIOB->MODER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOB->MODER|=(Copy_uddtMode<<(Copy_uddtPin*2));
			break;
			case PORTC:
			GPIOC->MODER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOC->MODER|=(Copy_uddtMode<<(Copy_uddtPin*2));
			break;
		}
	}
		
}

void MGPIO_voidSetOutputConfig(Port_t Copy_uddtPort,PIN_t Copy_uddtPin,Output_t Copy_uddtType,Speed_t Copy_uddtSpeed)
{
	if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		
	}
	else
	{
		switch(Copy_uddtPort)
		{
			case PORTA:
			GPIOA->OTYPER&=~(1<<Copy_uddtPin);
			GPIOA->OTYPER|=(Copy_uddtType<<Copy_uddtPin);
			GPIOA->OSPEEDER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOA->OSPEEDER|=(Copy_uddtSpeed<<(Copy_uddtPin*2));
			break;
			case PORTB:
			GPIOB->OTYPER&=~(1<<Copy_uddtPin);
			GPIOB->OTYPER|=(Copy_uddtType<<Copy_uddtPin);
			GPIOB->OSPEEDER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOB->OSPEEDER|=(Copy_uddtSpeed<<(Copy_uddtPin*2));
			break;
			case PORTC:
			GPIOC->OTYPER&=~(1<<Copy_uddtPin);
			GPIOC->OTYPER|=(Copy_uddtType<<Copy_uddtPin);
			GPIOC->OSPEEDER&=~(MUSK<<(Copy_uddtPin*2));
			GPIOC->OSPEEDER|=(Copy_uddtSpeed<<(Copy_uddtPin*2));
			break;
		}
	}
}

void MGPIO_voidSetPinValue(Port_t Copy_uddtPort,PIN_t Copy_uddtPin,PinValue_t Copy_uddtPinValue)
{
	if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		
	}
	else
	{
		switch(Copy_uddtPort)
		{
			case PORTA:
			GPIOA->ODR&=~(1<<Copy_uddtPin);
			GPIOA->ODR|=(Copy_uddtPinValue<<Copy_uddtPin);
			break;
			case PORTB:
			GPIOB->ODR&=~(1<<Copy_uddtPin);
			GPIOB->ODR|=(Copy_uddtPinValue<<Copy_uddtPin);
			break;
			case PORTC:
			GPIOC->ODR&=~(1<<Copy_uddtPin);
			GPIOC->ODR|=(Copy_uddtPinValue<<Copy_uddtPin);
			break;
		}
	}
}
void MGPIO_voidSetPinValueAtomic(Port_t Copy_uddtPort,PIN_t Copy_uddtPin,PinValue_t Copy_uddtPinValue)
{
	if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		
	}
	else
	{
		if(Copy_uddtPinValue==LOW)
		{
			Copy_uddtPin+=16;
		}
		switch(Copy_uddtPort)
		{
			case PORTA:
			GPIOA->BSRR=(1<<Copy_uddtPin);
			break;
			case PORTB:
			GPIOB->BSRR=(1<<Copy_uddtPin);
			break;
			case PORTC:
			GPIOC->BSRR=(1<<Copy_uddtPin);
			break;
		}
	}
}

void MGPIO_voidSetInputConfig(Port_t Copy_uddtPort,PIN_t Copy_uddtPin,Input_t Copy_uddtType)
{	
	if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		
	}
	else
	{
		switch(Copy_uddtPort)
		{
			case PORTA:
			GPIOA->PUPDR&=~(MUSK<<(Copy_uddtPin*2));
			GPIOA->PUPDR|=(Copy_uddtType<<(Copy_uddtPin*2));
			break;
			case PORTB:
			GPIOB->PUPDR&=~(MUSK<<(Copy_uddtPin*2));
			GPIOB->PUPDR|=(Copy_uddtType<<(Copy_uddtPin*2));
			break;
			case PORTC:
			GPIOC->PUPDR&=~(MUSK<<(Copy_uddtPin*2));
			GPIOC->PUPDR|=(Copy_uddtType<<(Copy_uddtPin*2));
			break;
		}
	}
}

u8 MGPIO_u8GetPinValue(Port_t Copy_uddtPort,PIN_t Copy_uddtPin)
{
	u8 Local_u8Value;
	if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		
	}
	else
	{
		switch(Copy_uddtPort)
		{
			case PORTA:
			Local_u8Value=GET_BIT(GPIOA->IDR,Copy_uddtPin);
			break;
			case PORTB:
			Local_u8Value=GET_BIT(GPIOB->IDR,Copy_uddtPin);
			break;
			case PORTC:
			Local_u8Value=GET_BIT(GPIOC->IDR,Copy_uddtPin);
			break;
		}
	}
	return Local_u8Value;
}

void MGPIO_voidSetAlternativeConfig(Port_t Copy_uddtPort,PIN_t Copy_uddtPin,Alternative_t Copy_uddtType)
{
	if(Copy_uddtPort==PORTA && (Copy_uddtPin==13 ||Copy_uddtPin==14 ||Copy_uddtPin==15))
	{
		
	}
	else if(Copy_uddtPort==PORTB && (Copy_uddtPin==3 ||Copy_uddtPin==4 ||Copy_uddtPin==5))
	{
		
	}
	else
	{
		switch(Copy_uddtPort)
		{
			case PORTA:
			if(Copy_uddtPin<8)
			{
				GPIOA->AFRL&=~(ALT_MUSK<< (Copy_uddtPin*4));
				GPIOA->AFRL|=(Copy_uddtType<<(Copy_uddtPin*4));
			}
			else if(Copy_uddtPin<16)
			{
				Copy_uddtPin-=8;
				GPIOA->AFRH&=~(ALT_MUSK<<(Copy_uddtPin*4));
				GPIOA->AFRH|=(Copy_uddtType<<(Copy_uddtPin*4));
			}
			break;
			case PORTB:
			if(Copy_uddtPin<8)
			{
				GPIOB->AFRL&=~(ALT_MUSK<< (Copy_uddtPin*4));
				GPIOB->AFRL|=(Copy_uddtType<<(Copy_uddtPin*4));
			}
			else if(Copy_uddtPin<16)
			{
				Copy_uddtPin-=8;
				GPIOC->AFRH&=~(ALT_MUSK<<(Copy_uddtPin*4));
				GPIOC->AFRH|=(Copy_uddtType<<(Copy_uddtPin*4));
			}
			break;
			case PORTC:
			if(Copy_uddtPin<8)
			{
				GPIOC->AFRL&=~(ALT_MUSK<< (Copy_uddtPin*4));
				GPIOC->AFRL|=(Copy_uddtType<<(Copy_uddtPin*4));
			}
			else if(Copy_uddtPin<16)
			{
				Copy_uddtPin-=8;
				GPIOC->AFRH&=~(ALT_MUSK<<(Copy_uddtPin*4));
				GPIOC->AFRH|=(Copy_uddtType<<(Copy_uddtPin*4));
			}
			break;
		}
	}
}


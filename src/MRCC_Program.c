/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MRCC_Program.c                                                          */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* Reset and Clock Control (RCC) driver for STM32 microcontrollers.                    */
/* Provides APIs to initialize the system clock and manage peripheral clocks.          */
/*                                                                                     */
/* Features:                                                                           */
/*   - Initializes system clock (HSI, HSE, or PLL).                                   */
/*   - Enables/disables peripheral clocks on AHB and APB buses.                        */
/*   - Configures clock source and oscillator modes.                                   */
/***************************************************************************************/

#include "STD_TYPES.H"
#include "BIT_MATH.h"

#include "MRCC_Interface.h"
#include "MRCC_Private.h"
#include "MRCC_Config.h"

void MRCC_voidInit(void)
{
	#if (SYSTEM_CLK==HSI_CLOCK)
		//HSI ON
		RCC->CR|=(1<<HSION);
		//Wait till HSI ready
		while(!GET_BIT(RCC->CR,HSIRDY));
		//Switch to HSI
		RCC->CFGR&=~(SW_MUSK<<SW0);
		RCC->CFGR|=(HSI_oscillator<<SW0);
	#elif (SYSTEM_CLK==HSE_CLOCK)
		#if(HSE_OSC==MECHANICAL_CLOCK)
			RCC->CR&=~(1<<HSEBYP);
		#elif (HSE_OSC==RC_CLOCK)
			RCC->CR|=(1<<HSEBYP);
		#endif
		
		//HSE ON
		RCC->CR|=(1<<HSEON);
		//Wait till HSE ready
		while(!GET_BIT(RCC->CR,HSERDY));
		//Switch to HSE
		RCC->CFGR&=~(SW_MUSK<<SW0);
		RCC->CFGR|=(HSE_oscillator<<SW0);
		//Disable HSI Clock
		RCC->CR&=~(1<<HSION);
		
	#elif (SYSTEM_CLK==PLL)
		
	#endif
}

void MRCC_voidEnablePeripheralClock(System_Bus_t Copy_uddtBus,u8 Copy_u8Peripheral)
{
	switch(Copy_uddtBus)
	{
		case AHB1_BUS:
		RCC->AHB1ENR|=(1<<Copy_u8Peripheral);
		break;
		case AHB2_BUS:
		RCC->AHB2ENR|=(1<<Copy_u8Peripheral);
		break;
		case APB1_BUS:
		RCC->APB1ENR|=(1<<Copy_u8Peripheral);
		break;
		case APB2_BUS:
		RCC->APB2ENR|=(1<<Copy_u8Peripheral);
		break;
		default:
		break;
	}
}

void MRCC_voidDisablePeripheralClock(System_Bus_t Copy_uddtBus,u8 Copy_u8Peripheral)
{
	switch(Copy_uddtBus)
	{
		case AHB1_BUS:
		RCC->AHB1ENR&=~(1<<Copy_u8Peripheral);
		break;
		case AHB2_BUS:
		RCC->AHB2ENR&=~(1<<Copy_u8Peripheral);
		break;
		case APB1_BUS:
		RCC->APB1ENR&=~(1<<Copy_u8Peripheral);
		break;
		case APB2_BUS:
		RCC->APB2ENR&=~(1<<Copy_u8Peripheral);
		break;
		default:
		break;
	}
}

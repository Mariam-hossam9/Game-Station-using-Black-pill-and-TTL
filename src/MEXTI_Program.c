/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MEXTI_Program.c                                                         */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* External Interrupt (EXTI) driver for STM32 microcontrollers.                        */
/* Provides configuration and control of interrupt lines.                              */
/*                                                                                     */
/* Features:                                                                           */
/*   - Selects interrupt port and line.                                                */
/*   - Enables/disables EXTI lines.                                                    */
/*   - Configures trigger mode (rising, falling, both).                                */
/*   - Registers callback functions for EXTI interrupts.                               */
/***************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "MEXTI_Interface.h"
#include "MEXTI_Private.h"
#include "MEXTI_Config.h"

static void(*Global_PtrEXTI[16])(void)={NULL};
void MEXTI_voidSetInterruptPort(EXTI_Line_t Copy_uddtLine,EXTI_Port_t Copy_uddtPort)
{
	SYSCFG->EXTICR[Copy_uddtLine/SYS_DIV]&=~(SYS_MUSK<<((Copy_uddtLine%SYS_DIV)*4));
	SYSCFG->EXTICR[Copy_uddtLine/SYS_DIV]|=(Copy_uddtPort<<((Copy_uddtLine%SYS_DIV)*4));
}

void MEXTI_voidEnable(EXTI_Line_t Copy_uddtLine)
{
	EXTI->IMR|=(1<<Copy_uddtLine);
}
void MEXTI_voidDisable(EXTI_Line_t Copy_uddtLine)
{
	EXTI->IMR&=~(1<<Copy_uddtLine);
}
void MEXTI_voidSetTrigger(EXTI_Line_t Copy_uddtLine,EXTI_TriggerMode_t Copy_uddtMode)
{
	switch(Copy_uddtMode)
	{
	case EXTI_Falling:
		EXTI->RTSR&=~(1<<Copy_uddtLine);
		EXTI->FTSR|=(1<<Copy_uddtLine);
		break;
	case EXTI_Rising:
		EXTI->RTSR|=(1<<Copy_uddtLine);
		EXTI->FTSR&=~(1<<Copy_uddtLine);
		break;
	case EXTI_OnChange:
		EXTI->RTSR|=(1<<Copy_uddtLine);
		EXTI->FTSR|=(1<<Copy_uddtLine);
		break;
	default:
		break;
	}
}


void MEXTI_voidCallBack(void(*ptr)(void),EXTI_Line_t Copy_uddtLine)
{
	if(Copy_uddtLine<16)
	{
		Global_PtrEXTI[Copy_uddtLine]=ptr;
	}
}

void EXTI0_IRQHandler()
{
	if(Global_PtrEXTI[0]!=NULL)
	{
		Global_PtrEXTI[0]();
		// Clear the pending flag for EXTI0
		EXTI->PR|=(1<<0);
	}
}

void EXTI15_10_IRQHandler()
{
	if(Global_PtrEXTI[12]!=NULL)
	{
		Global_PtrEXTI[12]();
		// Clear the pending flag for EXTI0
		EXTI->PR|=(1<<0);
	}
}

void EXTI3_IRQHandler()
{
	if(Global_PtrEXTI[3]!=NULL)
	{
		Global_PtrEXTI[3]();
		// Clear the pending flag for EXTI0
		EXTI->PR|=(1<<0);
	}
}

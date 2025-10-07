/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MSTK_Program.c                                                          */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/*                                                                                     */
/* Description:                                                                        */
/* SysTick (System Timer) driver for STM32 microcontrollers.                           */
/* Provides time delays and callback-based periodic interrupts.                        */
/*                                                                                     */
/* Features:                                                                           */
/*   - Configures SysTick with AHB or AHB/8 clock source.                              */
/*   - Supports blocking delay in milliseconds or microseconds.                        */
/*   - Provides single-shot and periodic callbacks using SysTick interrupts.            */
/*   - Reads elapsed and remaining tick counts.                                        */
/*                                                                                     */
/* Usage:                                                                              */
/*   1. Call `MSTK_voidInit()` to configure SysTick clock.                             */
/*   2. Use `MSTK_voidDelayms()` or `MSTK_voidDelayus()` for precise delays.           */
/*   3. Register callback with `MSTK_voidCallBack()` or `_Single()` if needed.          */
/***************************************************************************************/

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "MSTK_Interface.h"
#include "MSTK_Private.h"
#include "MSTK_Config.h"

static void (*Global_ptr)(void)=NULL;
static volatile u8 flag=0;
void MSTK_voidInit()
{
#if (STK_SYSTEM_CLK==STK_AHB_8)
	STK->CTRL&=~(1<<CLOCK_SOURCE);
	STK->CTRL&=~(1<<STK_ENABLE);
#elif (STK_SYSTEM_CLK==STK_AHB)
	STK->CTRL|=(1<<CLOCK_SOURCE);
	STK->CTRL&=~(1<<STK_ENABLE);
#endif
}
void MSTK_voidStartTimer(u32 Copy_u32ReloadValue)
{
	STK->LOAD=Copy_u32ReloadValue;
	STK->VAL=0;
	STK->CTRL|=(1<<STK_ENABLE);
}
void MSTK_voidCtrlIntState(STK_IntState Copy_uddtIntState)
{
	STK->CTRL|=(Copy_uddtIntState<<TICKINT);
}
u8 MSTK_u8ReadFlag()
{
	return GET_BIT(STK->CTRL,COUNT_FLAG);
}
/*Function in Single shot*/
u32 MSTK_u32GetElapsedTickSingleShot()
{
	return ((STK->LOAD)-(STK->VAL));
}
u32 MSTK_u32GetRemainingTickSingleShot()
{
	return (STK->VAL);
}

void MSTK_voidDelayms(u32 Copy_u32Delayms)
{
	MSTK_voidCtrlIntState(Systick_IntDisable);
	MSTK_voidStartTimer(Copy_u32Delayms*2000);
	while(MSTK_u8ReadFlag()==0);
	STK->CTRL&=~(1<<STK_ENABLE);
}
void MSTK_voidDelayus(u32 Copy_u32Delayus)
{
	MSTK_voidCtrlIntState(Systick_IntDisable);
	MSTK_voidStartTimer(Copy_u32Delayus*2);
	while(MSTK_u8ReadFlag()==0);
	STK->CTRL&=~(1<<STK_ENABLE);
}

void MSTK_voidCallBack(void(*ptr)(void), u32 Copy_u32TickTime)
{
	flag=0;
	Global_ptr=ptr;
	MSTK_voidStartTimer(Copy_u32TickTime*2);
}

void MSTK_voidCallBackSingle(void(*ptr)(void), u32 Copy_u32TickTime)
{
	flag=1;
	Global_ptr=ptr;
	MSTK_voidStartTimer(Copy_u32TickTime*2);
}

void SysTick_Handler()
{
	if(Global_ptr!=NULL)
	{
		Global_ptr();
	}
	if(flag==1)
	{
		MSTK_voidCtrlIntState(Systick_IntDisable);
	}
}

u32 MSTK_u32GetCurrentValue(void)
{
    return STK->VAL;
}

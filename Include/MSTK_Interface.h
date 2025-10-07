/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MSTK_INTERFACE.h                                                        */
/* Date      : October 8, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Interface file for SysTick timer driver.                               */
/*              Provides initialization, delay, and interrupt control APIs.            */
/***************************************************************************************/

#ifndef MSTK_INTERFACE_H
#define MSTK_INTERFACE_H

typedef enum {
	Systick_IntDisable = 0,
	Systick_IntEnable
} STK_IntState;

void MSTK_voidInit(void);
void MSTK_voidStartTimer(u32 Copy_u32ReloadValue);
void MSTK_voidCtrlIntState(STK_IntState Copy_uddtIntState);
u8 MSTK_u8ReadFlag(void);

/* Functions in single-shot mode */
u32 MSTK_u32GetElapsedTickSingleShot(void);
u32 MSTK_u32GetRemainingTickSingleShot(void);

/* Delay functions */
void MSTK_voidDelayms(u32 Copy_u32Delayms);
void MSTK_voidDelayus(u32 Copy_u32Delayus);

/* Callback functions */
void MSTK_voidCallBack(void (*ptr)(void), u32 Copy_u32TickTime);
void MSTK_voidCallBackSingle(void (*ptr)(void), u32 Copy_u32TickTime);

#endif

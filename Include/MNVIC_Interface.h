/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MNVIC_Interface.h                                                       */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Interface file for Nested Vector Interrupt Controller (NVIC) driver.   */
/*              Provides APIs for enabling, disabling, and prioritizing interrupts.    */
/***************************************************************************************/
#ifndef MNVIC_INTERFACE_H
#define MNVIC_INTERFACE_H

typedef enum{
	Group16Sub0 = 3,
	Group8Sub2,
	Group4Sub4,
	Group2Sub8,
	Group0Sub16
}NVIC_Group_t;

/* Enable & Disable NVIC */
void MNVIC_voidEnable(u8 Copy_u8Position);
void MNVIC_voidDisable(u8 Copy_u8Position);
/* Set & Clear Pending Flag */
void MNVIC_voidSetPendingFlag(u8 Copy_u8Position);
void MNVIC_voidClearPendingFlag(u8 Copy_u8Position);
/* Read Active Flag */
u8 MNVIC_u8ReadingActiveState(u8 Copy_u8Position);
/* Group and Subgroup Configuration */
void MNVIC_voidSetGroupMode(NVIC_Group_t Copy_uddtGroupMode);
void MNVIC_voidSetInterruptPriority(u8 Copy_u8Position, u8 Copy_u8Group, u8 Copy_u8SubGroup);

#endif

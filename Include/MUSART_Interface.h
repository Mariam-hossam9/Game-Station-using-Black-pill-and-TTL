/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MUSART_INTERFACE.h                                                      */
/* Date      : October 8, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Interface file for USART driver.                                       */
/*              Provides initialization, data transmission, and reception APIs.        */
/***************************************************************************************/

#ifndef MUSART_INTERFACE_H
#define MUSART_INTERFACE_H

extern volatile u8 quit_flag;

void MUSART_voidInit(void);
void MUSART_voidSendData(u8 Copy_u8Data);
u8   MUSART_u8RecieveData(void);

void MUSART_voidSendString(u8 *Copy_pu8Str);
void MUSART_voidRecieveString(u8 *Copy_pu8Str);

void USART1_IRQHandler(void);

#endif

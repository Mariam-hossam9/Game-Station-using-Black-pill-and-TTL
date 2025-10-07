/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : HSTP_Interface.h                                                        */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Interface file for Serial-to-Parallel (Shift Register) driver.          */
/*              Provides configuration and function prototypes for serial data output. */
/***************************************************************************************/
#ifndef HSTP_INTERFACE_H
#define HSTP_INTERFACE_H

#define HSTP_PORT    PORTA

#define SDI      PIN0
#define SHIFT    PIN1
#define LATCH    PIN2

void HSTP_voidInit();
void HSTP_voidShiftData(u8 Copy_u8Data);
void HSTP_voidSendData();

#endif

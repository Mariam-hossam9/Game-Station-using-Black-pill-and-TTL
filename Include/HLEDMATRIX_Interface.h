/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : HLEDMATRIX_Interface.h                                                  */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Interface file for LED Matrix driver.                                  */
/*              Provides function prototypes for initialization and display control.   */
/***************************************************************************************/
#ifndef HLEDMATRIX_INTERFACE_H
#define HLEDMATRIX_INTERFACE_H

void HLEDMATRIX_voidInit();
void HLEDMATRIX_voidDisplay(u8* Copy_pu8Arr);

#endif

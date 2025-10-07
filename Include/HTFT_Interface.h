/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : HTFT_Interface.h                                                        */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Interface file for TFT display driver.                                 */
/*              Declares APIs for display initialization and image rendering.          */
/***************************************************************************************/
#ifndef HTFT_INTERFACE_H_
#define HTFT_INTERFACE_H_

void HTFT_voidInit();
void HTFT_voidDisplay(const u16* Copy_pu16PTR);

#endif /* HTFT_INTERFACE_H_ */

/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MSPI_Interface.h                                                        */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Interface file for the SPI (Serial Peripheral Interface) driver.       */
/*              Provides APIs for SPI initialization and full-duplex data exchange.    */
/***************************************************************************************/
#ifndef MSPI_INTERFACE_H_
#define MSPI_INTERFACE_H_

void MSPI_voidMasterInit();
void MSPI_voidSlaveInit();
u16  MSPI_u16Tranceive(u16 Copy_u16Data);

#endif /* MSPI_INTERFACE_H_ */

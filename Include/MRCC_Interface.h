/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MRCC_Interface.h                                                        */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Interface file for the RCC (Reset and Clock Control) driver.           */
/*              Provides APIs to initialize the system clock and control peripheral     */
/*              clock enable/disable on AHB1, AHB2, APB1, and APB2 buses.              */
/***************************************************************************************/
#ifndef MRCC_INTERFACE_H
#define MRCC_INTERFACE_H

typedef enum{
	AHB1_BUS=0,
	AHB2_BUS,
	APB1_BUS,
	APB2_BUS
}System_Bus_t;

void MRCC_voidInit(void);
void MRCC_voidEnablePeripheralClock(System_Bus_t Copy_uddtBus,u8 Copy_u8Peripheral);
void MRCC_voidDisablePeripheralClock(System_Bus_t Copy_uddtBus,u8 Copy_u8Peripheral);

/***************** AHB1 *****************/
#define AHB1_GPIOA    0
#define AHB1_GPIOB    1
#define AHB1_GPIOC    2
#define AHB1_DMA1     21
#define AHB1_DMA2     22

/***************** APB1 *****************/
#define APB1_SPI2     15
#define APB1_SPI3     16
#define APB1_USART2   17
#define APB1_I2C1     21
#define APB1_I2C2     22
#define APB1_I2C3     23

/***************** APB2 *****************/
#define APB2_USART1   4
#define APB2_USART6   17
#define APB2_SPI1     12    
#define APB2_SPI4     13 
#define APB2_SYSCFG   14

#endif

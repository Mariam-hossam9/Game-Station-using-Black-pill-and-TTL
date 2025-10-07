/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MRCC_Config.h                                                           */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Configuration file for the RCC (Reset and Clock Control) driver.       */
/*              Used to select the system clock source and HSE oscillator type.        */
/***************************************************************************************/
#ifndef MRCC_CONFIG_H
#define MRCC_CONFIG_H

/* Choose Between:
 * 1 - HSI_CLOCK
 * 2 - HSE_CLOCK
 * 3 - PLL
 */
#define SYSTEM_CLK     HSI_CLOCK

/* Choose between:
 * 1 - MECHANICAL_CLOCK
 * 2 - RC_CLOCK
 */
#define HSE_OS   MECHANICAL_CLOCK

#endif

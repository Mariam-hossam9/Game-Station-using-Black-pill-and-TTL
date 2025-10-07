/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MSTK_CONFIG.h                                                           */
/* Date      : October 8, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Configuration file for SysTick timer driver.                           */
/*              Selects the system clock source for the SysTick timer.                 */
/***************************************************************************************/

#ifndef MSTK_CONFIG_H
#define MSTK_CONFIG_H

/* Choose Between:
 * 1 - STK_AHB
 * 2 - STK_AHB_8
 */
#define STK_SYSTEM_CLK   STK_AHB_8

#endif

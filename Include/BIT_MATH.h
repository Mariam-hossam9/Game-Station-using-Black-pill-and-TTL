/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : BIT_MATH.h                                                              */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: This file contains bit manipulation macros (SET_BIT, CLR_BIT, etc.)    */
/*              used across all drivers and applications.                              */
/***************************************************************************************/

#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define SET_BIT(VAR,BITNO) (VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO) (VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO) (VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO) (((VAR) >> (BITNO)) & 0x01)
#define NULL    ((void*)0)

#endif

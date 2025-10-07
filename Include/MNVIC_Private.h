/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MNVIC_Private.h                                                         */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Private file for NVIC register mapping and internal definitions.       */
/*              Includes base addresses, structure layout, and SCB AIRCR macros.       */
/***************************************************************************************/
#ifndef MNVIC_PRIVATE_H
#define MNVIC_PRIVATE_H

#define NVIC_BASE_ADDRESS  (0xE000E100)

typedef struct{
	u32 ISER[8];
	u32 Reserved0[24];
	u32 ICER[8];
	u32 Reserved1[24];
	u32 ISPR[8];
	u32 Reserved2[24];
	u32 ICPR[8];
	u32 Reserved3[24];
	u32 IABR[8];
	u32 Reserved4[56];
	u8  IPR[240];
	u32 Reserved5[580];
	u32 STIR;
}NVIC_t;

#define NVIC     ((volatile NVIC_t*)NVIC_BASE_ADDRESS)
#define REG_DIV  32

/*********************** IN SCB Driver ************************/
#define SCB_AIRCR  (*(volatile u32*)(0xE000ED0C))
#define VECTKEY    0x05FA0000

#endif

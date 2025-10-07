/******************************************************************************
 * @file    MSTK_PRIVATE.h
 * @author  Mariam
 * @version 1.0
 * @date    08-Oct-2025
 * @brief   Private definitions and register mapping for SysTick timer (MSTK)
 * @note    Based on ARM Cortex-M4 SysTick peripheral reference.
 ******************************************************************************/

#ifndef MSTK_PRIVATE_H_
#define MSTK_PRIVATE_H_

#define MSTK_BASE_ADDRESS     (0xE000E010)

typedef struct {
	u32 CTRL;
	u32 LOAD;
	u32 VAL;
	u32 CALIB;
} MSTK_t;

#define STK   ((volatile MSTK_t*)MSTK_BASE_ADDRESS)

/* Bit definitions */
#define COUNT_FLAG     16
#define CLOCK_SOURCE   2
#define TICKINT        1
#define STK_ENABLE     0

/* Clock source options */
#define STK_AHB        0
#define STK_AHB_8      1

#endif

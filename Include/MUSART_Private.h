/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : MUSART_PRIVATE.h                                                        */
/* Date      : October 8, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Private register definitions and structures for USART driver.          */
/*              Includes bit-field mapping of control registers and base address.      */
/***************************************************************************************/

#ifndef MUSART_PRIVATE_H
#define MUSART_PRIVATE_H

#define USART1_BASE_ADDRESS   (0x40011000)

/* USART_CR1 Bitfield Structure */
typedef struct {
    u32 SBK       : 1;
    u32 RWU       : 1;
    u32 RE        : 1;
    u32 TE        : 1;
    u32 IDLEIE    : 1;
    u32 RXNEIE    : 1;
    u32 TCIE      : 1;
    u32 TXEIE     : 1;
    u32 PEIE      : 1;
    u32 PS        : 1;
    u32 PCE       : 1;
    u32 WAKE      : 1;
    u32 M         : 1;
    u32 UE        : 1;
    u32 Reserved  : 1;
    u32 OVER8     : 1;
    u32 Reserved2 : 16;
} USART_CR1;

/* USART Register Map */
typedef struct {
    u32 SR;        /* Status register */
    u32 DR;        /* Data register */
    u32 BRR;       /* Baud rate register */
    USART_CR1 CR1; /* Control register 1 */
    u32 CR2;       /* Control register 2 */
    u32 CR3;       /* Control register 3 */
    u32 GTPR;      /* Guard time and prescaler */
} USART_t;

/* USART1 Peripheral Base */
#define USART1    ((volatile USART_t *) USART1_BASE_ADDRESS)

/* Bit Positions */
#define TXE   7
#define RXNE  5

#endif

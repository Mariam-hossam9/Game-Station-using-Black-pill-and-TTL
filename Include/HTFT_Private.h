/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : HTFT_Private.h                                                          */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Private file for TFT display driver.                                   */
/*              Contains static helper functions and internal command definitions.     */
/***************************************************************************************/
#ifndef HTFT_PRIVATE_H_
#define HTFT_PRIVATE_H_

static void HTFT_voidWriteData(u8 Copy_u8Data);
static void HTFT_voidWriteCommand(u8 Copy_u8CMD);

// Commands
#define SLEEP_OUT    0x11
#define COLOR_MODE   0x3A
#define DISPLAY_ON   0x29
#define X_DIRECTION  0x2A
#define Y_DIRECTION  0x2B
#define SCREEN_WRITE 0x2C

// Image Size
#define IMAGE_SIZE   20480

// RGB565 Color Mode
#define RGB565   0x05

#endif /* HTFT_PRIVATE_H_ */

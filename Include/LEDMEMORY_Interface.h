
/***************************************************************************************/
// Author: Mariam Hossam
// Name: LedMemory_Interface.h
// Date: September 15, 2025
// Description: This file contains the interface for the Led Memory game.
//              It defines the functions and pins used to interact with game pins.

/**************************************************************************************/
#ifndef LEDMEMORY_INTERFACE_H_
#define LEDMEMORY_INTERFACE_H_

#include "STD_TYPES.h"

// Configuration
#define LED_PORT PORTB
#define LED_PIN0 PIN0
#define LED_PIN1 PIN1
#define LED_PIN2 PIN2

#define BTN_PORT PORTA
#define BTN_PIN0 PIN2
#define BTN_PIN1 PIN3
#define BTN_PIN2 PIN4
#define MAX_SEQUENCE_LENGTH 10
extern u8 rx_data;
// Public APIs
void Game_Init(void);
void Game_Run(void);


#endif /* LEDMEMORY_INTERFACE_H_ */

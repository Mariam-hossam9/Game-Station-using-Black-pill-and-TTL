/***************************************************************************************/
/* Author    : Mariam Hossam                                                           */
/* File      : HTFT_Config.h                                                           */
/* Date      : August 21, 2025                                                         */
/* Version   : V1.0                                                                    */
/* Description: Configuration file for TFT display driver.                             */
/*              Defines port and pin assignments, as well as screen dimensions.        */
/***************************************************************************************/
#ifndef HTFT_CONFIG_H_
#define HTFT_CONFIG_H_

#define TFT_PORT      PORTA
#define RST_PIN       PIN0
#define CONTROL_PIN   PIN1

// Start & End X
#define START_X_B0  0
#define START_X_B1  0
#define END_X_B0    0
#define END_X_B1   127

// Start & End Y
#define START_Y_B0  0
#define START_Y_B1  0
#define END_Y_B0    0
#define END_Y_B1   159

#endif /* HTFT_CONFIG_H_ */

/***************************************************************************************/
// Author: Mariam Hossam
// Name: snake.h
// Date: September 15, 2025
// Description: This file contains the interface for the snake game.
//              It defines the functions and pins used to interact with game pins.

/**************************************************************************************/

#ifndef SNAKE_H_
#define SNAKE_H_

#include "STD_TYPES.h"



#define WIDTH       128
#define HEIGHT      160
#define CUBE_SIZE   8
#define BG_COLOR    0x0000  // black
#define APPLE_COLOR 0xF800  // red
#define SNAKE_COLOR 0x07E0  // green


typedef struct {
	s16 x;
    s16 y;
} Point;

typedef struct {
    Point body[128];  // supports up to 128 segments
    u8 length;
    Point dir;
    Point apple;
    Point last_removed;
} SnakeGame;

extern u8 rx_data;
static u16 frameBuffer[WIDTH * HEIGHT];
static SnakeGame game;

// Button Pins on PORTA
#define BTN1   PIN2  // PA2
#define BTN2   PIN3  // PA3
#define BTN3   PIN4  // PA4

void Snake_Init(SnakeGame* g);
void Snake_Draw(SnakeGame* g, u16* fb);
void Snake_Move(SnakeGame* g);
void Snake_NewApple(SnakeGame* g);
void Snake_CheckCollision(SnakeGame* g);
void Snake_GoUp(SnakeGame* g);
void Snake_GoDown(SnakeGame* g);
void Snake_GoLeft(SnakeGame* g);
void Snake_GoRight(SnakeGame* g);
void configureButtons();
void checkButtons();
void Snake_RunGame(void);

#endif

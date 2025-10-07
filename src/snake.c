/***************************************************************************************/
// Author: Mariam Hossam
// Name: snake.c
// Date: September 15, 2025
// Description: This file contains the interface for the snake game.
//              It defines the functions and pins used to interact with game pins.

/**************************************************************************************/

#include "snake.h"
#include <stdlib.h>
#include"MRCC_Interface.h"
#include"MGPIO_Interface.h"
#include"HTFT_Interface.h"
#include"TFT_Image7.h"

extern SnakeGame game;
extern u16 frameBuffer[WIDTH * HEIGHT];

volatile u8 quit_flag = 0;
void Snake_RunGame(void)
{
    configureButtons();
    Snake_Init(&game);
    // Step 1
	HTFT_voidDisplay(Image7_ARR);
	MSTK_voidDelayms(2000);

    while (1)
    {
    	Snake_Draw(&game, frameBuffer);
		HTFT_voidDisplay(frameBuffer);
		checkButtons();
		Snake_Move(&game);
		Snake_CheckCollision(&game);
		MSTK_voidDelayms(150);
		if (quit_flag)
		        break;
    }
}
static inline void drawRect(u16* fb, s16 x, s16 y, s16 w, s16 h, u16 color) {
    if (x < 0 || y < 0 || x+w > WIDTH || y+h > HEIGHT) return;
    for (s16 yy = y; yy < y+h; yy++) {
        for (s16 xx = x; xx < x+w; xx++) {
            fb[yy * WIDTH + xx] = color;
        }
    }
}

void Snake_Init(SnakeGame* g) {
    g->length = 5;
    for (u8 i=0; i<g->length; i++) {
        g->body[i].x = 5 - i;
        g->body[i].y = 5;
    }
    g->dir.x = 1;
    g->dir.y = 0;
    Snake_NewApple(g);
}

void Snake_Draw(SnakeGame* g, u16* fb) {
    // Clear screen
    for (u32 i=0; i<WIDTH*HEIGHT; i++) fb[i] = BG_COLOR;

    // Draw apple
    drawRect(fb, g->apple.x * CUBE_SIZE, g->apple.y * CUBE_SIZE,
             CUBE_SIZE, CUBE_SIZE, APPLE_COLOR);

    // Draw snake
    for (u8 i=0; i<g->length; i++) {
        drawRect(fb, g->body[i].x * CUBE_SIZE, g->body[i].y * CUBE_SIZE,
                 CUBE_SIZE, CUBE_SIZE, SNAKE_COLOR);
    }
}

void Snake_Move(SnakeGame* g) {
    // Remove tail (save for redraw)
    g->last_removed = g->body[g->length-1];

    for (int i=g->length-1; i>0; i--) {
        g->body[i] = g->body[i-1];
    }

    g->body[0].x += g->dir.x;
    g->body[0].y += g->dir.y;

    // Wrap around screen
    if (g->body[0].x < 0) g->body[0].x = (WIDTH / CUBE_SIZE) - 1;
    if (g->body[0].x >= (WIDTH / CUBE_SIZE)) g->body[0].x = 0;
    if (g->body[0].y < 0) g->body[0].y = (HEIGHT / CUBE_SIZE) - 1;
    if (g->body[0].y >= (HEIGHT / CUBE_SIZE)) g->body[0].y = 0;

    // Apple eaten?
    if (g->body[0].x == g->apple.x && g->body[0].y == g->apple.y) {
        if (g->length < 128) {
            g->body[g->length] = g->last_removed;
            g->length++;
        }
        Snake_NewApple(g);
    }
}

void Snake_CheckCollision(SnakeGame* g) {
    for (u8 i=1; i<g->length; i++) {
        if (g->body[0].x == g->body[i].x && g->body[0].y == g->body[i].y) {
            Snake_Init(g); // Reset on collision
            return;
        }
    }
}

void Snake_NewApple(SnakeGame* g) {
    u8 valid = 0;
    while (!valid) {
        g->apple.x = rand() % (WIDTH / CUBE_SIZE);
        g->apple.y = rand() % (HEIGHT / CUBE_SIZE);
        valid = 1;
        for (u8 i=0; i<g->length; i++) {
            if (g->apple.x == g->body[i].x && g->apple.y == g->body[i].y) {
                valid = 0;
                break;
            }
        }
    }
}

void Snake_GoUp(SnakeGame* g)    { if (g->dir.y == 0) { g->dir.x=0; g->dir.y=-1; } }
void Snake_GoDown(SnakeGame* g)  { if (g->dir.y == 0) { g->dir.x=0; g->dir.y= 1; } }
void Snake_GoLeft(SnakeGame* g)  { if (g->dir.x == 0) { g->dir.x=-1; g->dir.y= 0; } }
void Snake_GoRight(SnakeGame* g) { if (g->dir.x == 0) { g->dir.x= 1; g->dir.y= 0; } }

void configureButtons() {

	MRCC_voidEnablePeripheralClock(AHB1_BUS, AHB1_GPIOA);
	MRCC_voidEnablePeripheralClock(APB2_BUS, APB2_SPI1);

	// Configure SPI pins
	MGPIO_voidSetMode(PORTA, PIN4, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA, PIN4, AF5);

	MGPIO_voidSetMode(PORTA, PIN5, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA, PIN5, AF5);

	MGPIO_voidSetMode(PORTA, PIN6, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA, PIN6, AF5);

	MGPIO_voidSetMode(PORTA, PIN7, Alternative_Func);
	MGPIO_voidSetAlternativeConfig(PORTA, PIN7, AF5);

    // Configure buttons
    MGPIO_voidSetMode(PORTA, BTN1, INPUT);
    MGPIO_voidSetInputConfig(PORTA, BTN1, PULLUP);

    MGPIO_voidSetMode(PORTA, BTN2, INPUT);
    MGPIO_voidSetInputConfig(PORTA, BTN2, PULLUP);

    MGPIO_voidSetMode(PORTA, BTN3, INPUT);
    MGPIO_voidSetInputConfig(PORTA, BTN3, PULLUP);
	MSTK_voidInit();
    MSPI_voidMasterInit();
	HTFT_voidInit();
}

void checkButtons() {
    if (!MGPIO_u8GetPinValue(PORTA, BTN1)) Snake_GoUp(&game);
    if (!MGPIO_u8GetPinValue(PORTA, BTN2)) Snake_GoDown(&game);
    if (!MGPIO_u8GetPinValue(PORTA, BTN3)) Snake_GoLeft(&game);
    // optional: add right on another pin if available
}

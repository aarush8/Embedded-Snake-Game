// ============================================
// The Graphics file
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "graphics.h"
#include "globals.h"


#define WHITE 0xFFFFFF
#define BLACK 0x000000
#define RED   0xFF0000
#define GREEN 0x00FF00
#define BLUE  0x0000FF
#define LGREY 0xBFBFBF
#define DGREY 0x5F5F5F
#define YELLOW 0xFFFF00
#define BROWN  0xD2691E
#define ORANGE 0xFFA500
#define PURPLE 0xA020F0
#define CYAN   0x00D7FF  // Color for boost sprite

#include <stdint.h>


// 2035TODO
// You should create your own sprite, but feel free to use this one while setting up your game!
const char* fruit_img =
    "000BG000"
    "000B0000"
    "0RRRRRR0"
    "RRRRRRRR"
    "RRRRRRRR"
    "RRRRRRRR"
    "0RRRRRR0"
    "00RRRR00";

// Create a lightning bolt sprite for the boost item
const char* boost_img =
    "00CCCC00"
    "000CC000"
    "00CCCC00"
    "0CCCCCC0"
    "CCCCCC00"
    "0CCCC000"
    "00CC0000"
    "000C0000";

// New boost sprite 32x32 pixels
#define NEW_PISKEL_FRAME_COUNT 1
#define NEW_PISKEL_FRAME_WIDTH 32
#define NEW_PISKEL_FRAME_HEIGHT 32

/* Piskel data for "New Piskel" */
static const uint32_t boost_sprite_data[1][1024] = {
{
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00d7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0x00000000, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0xff00d7ff, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 
}
};

void draw_img(int x, int y, const char* img)
{
    // Convert char-based sprite data to int array that BLIT expects
    // Each character represents a color
    int colors[CELL_SIZE * CELL_SIZE];
    
    for (int i = 0; i < CELL_SIZE * CELL_SIZE; i++) {
        char c = img[i];
        // Map characters to colors
        switch(c) {
            case 'R': colors[i] = RED; break;
            case 'G': colors[i] = GREEN; break;
            case 'B': colors[i] = BLUE; break;
            case 'Y': colors[i] = YELLOW; break;
            case 'W': colors[i] = WHITE; break;
            case 'O': colors[i] = ORANGE; break;
            case 'P': colors[i] = PURPLE; break;
            case 'C': colors[i] = CYAN; break;
            case '0': colors[i] = BLACK; break;
            default: colors[i] = BLACK; break;
        }
    }
    
    // Now pass the int array to BLIT
    uLCD.BLIT(x*CELL_SIZE, y*CELL_SIZE, CELL_SIZE, CELL_SIZE, colors);
    wait_us(250); // Recovery time!
}

// 2035TODO
void draw_fruit(int x, int y)
{
    // 1. call draw_img OR uLCD.BLIT() to draw a custom sprite that you create
    // 2. OR implement functionality that draws a CELL_SIZExCELL_SIZE square using the uLCD.filled_rectangle function
    // Recall the grid structure of the uLCD screen.
    // CELL_SIZE is 8 in the provided code, and the real size of the uLCD screen is 128x128
    // filled_rectangle takes x1, y1, x2, y2 that define the bounding points (top left, bottom right) of a filled rectangle IN uLCD COORDINATES
    // you must convert the passed in x,y coordinates (which correspond to a 16x16 grid of cells) to uLCD coordinates before drawing the rectangle

    draw_img(x, y, fruit_img);

}

// 2035TODO
// the remainder of these functions should be handled the same way as draw_fruit
void draw_poison(int x, int y)
{   

    uLCD.filled_rectangle(
        x * CELL_SIZE,
        y * CELL_SIZE,
        (x + 1) * CELL_SIZE - 1,
        (y + 1) * CELL_SIZE - 1,
        PURPLE
    );


}

void draw_boost(int x, int y)
{
    // Draw the lightning bolt sprite for the boost item
    draw_img(x, y, boost_img);
}

void draw_snake_body(int x, int y)
{
    uLCD.filled_rectangle(
        x * CELL_SIZE,
        y * CELL_SIZE,
        (x + 1) * CELL_SIZE - 1,
        (y + 1) * CELL_SIZE - 1,
        GREEN // Snake body color
    );
}

void draw_snake_head(int x, int y)
{
    uLCD.filled_rectangle(
        x * CELL_SIZE,
        y * CELL_SIZE,
        (x + 1) * CELL_SIZE - 1,
        (y + 1) * CELL_SIZE - 1,
        BLUE // Snake head color
    );
}


void draw_nothing(int x, int y)
{
    uLCD.filled_rectangle(
        x * CELL_SIZE,
        y * CELL_SIZE,
        (x + 1) * CELL_SIZE - 1,
        (y + 1) * CELL_SIZE - 1,
        BLACK // Clear cell with background color
    );
}

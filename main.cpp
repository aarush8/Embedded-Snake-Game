//=================================================================
// The main program file.
//
// Copyright 2025 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//==================================================================

// External libs
#include <cstdio>
#include <stdlib.h>

// Project Includes
#include "globals.h"
#include "hardware.h"
#include "mbed_retarget.h"
#include "snake.h"
#include "items.h"
#include "doubly_linked_list.h"

#define TICK_RATE 2

// Function prototype for cleanupGame
void cleanupGame();

// Function prototype for draw_game_start_screen
void draw_game_start_screen();

// Implementation of draw_game_start_screen function
void draw_game_start_screen() {
    // Clear the screen
    uLCD.cls();
    
    // Display the game title
    uLCD.text_width(2);
    uLCD.text_height(2);
    uLCD.color(GREEN);
    uLCD.locate(1, 1);  // Moved up one line
    uLCD.printf("SNAKE");
    uLCD.locate(1, 3);  // Moved up one line
    uLCD.printf("GAME");
    
    // Reset text size and color for instructions
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.color(WHITE);
    
    // Display instructions - increased spacing
    uLCD.locate(1, 9);  // Increased from 8 to 9 to add more space after the large title
    uLCD.printf("Use joystick to move");
    uLCD.locate(1, 11); // Increased from 10 to 11
    uLCD.printf("Press any button");
    uLCD.locate(1, 12); // Increased from 11 to 12
    uLCD.printf("to start game");
}

int main()
{
    printf("Initialization starting\n");
    GameInputs inputs;
    ASSERT_P(hardware_init() == ERROR_NONE, -1);
    
    Timer t;
    t.start();

game_start:
    // Draw the new attractive start screen instead of just text
    draw_game_start_screen();

    // This loop is for the start screen
    // While the user has not provided an input, the game should remain on the start screen
    while(1){
        // 2035TODO
        // you need to implement read_inputs to get past the start screen!!
        inputs = read_inputs();
        if (inputs.up || inputs.down || inputs.right || inputs.left || inputs.center || inputs.b1 || inputs.b2 || inputs.b3) {
            srand(t.elapsed_time().count()); // this line sets the random seed
            break;
        }
    }

    uLCD.cls();

    // Cleanup any existing game data before starting a new game
    if (get_snake() != NULL) {
        cleanupGame();
    }

    // Initialize the Snake and the Items
    snake_init();
    items_init();

    uLCD.baudrate(115200);
    
    int tick = 0;
    bool game_over = false;
    
    // Main game loop
    while(1)
    {
        wait_us(40000); // Recovery time

        // 1. Draw the items and the snake
        draw_items();
        draw_snake();

        // 2. Print the score and the snake's 'boosted' value at the top of the screen
        uLCD.locate(0, 0);
        uLCD.printf("Score: %d  ", get_snake()->score);
        uLCD.locate(10, 0);
        uLCD.printf("Boost: %d", get_snake()->boosted);

        // 3. Check for collisions - if GAME-ENDING collision occurs, end the game with a game over screen
        
        // First check for wall collision
        if (check_wall_collision()) {
            uLCD.cls();
            uLCD.locate(2, 5);
            uLCD.printf("GAME OVER!");
            uLCD.locate(2, 7);
            uLCD.printf("Score: %d", get_snake()->score);
            uLCD.locate(2, 9);
            uLCD.printf("Press any button to restart");
            game_over = true;
            break;
        }

        // Process item collision before checking self collision
        // This way, if eating an item causes the snake to grow, the self-collision check
        // will include the new segment
        if (check_item_collision()) {
            //No longer need as we modified check_item_collision to handle poison differently
        }
        
        // Now check for self collision after handling item collision
        if (check_self_collision()) {
            uLCD.cls();
            uLCD.locate(2, 5);
            uLCD.printf("GAME OVER!");
            uLCD.locate(2, 7);
            uLCD.printf("Score: %d", get_snake()->score);
            uLCD.locate(2, 9);
            uLCD.printf("Press any button to restart");
            game_over = true;
            break;
        }

        // 4. Check if the snake's score >= 10 - if so end the game with a game win screen
        if (get_snake()->score >= 10) {
            uLCD.cls();
            uLCD.locate(2, 5);
            uLCD.printf("YOU WIN!");
            uLCD.locate(2, 7);
            uLCD.printf("Score: %d", get_snake()->score);
            uLCD.locate(2, 9);
            uLCD.printf("Press any button to restart");
            game_over = true;
            break;
        }

        // 5. Read the user inputs and update the snake direction if necessary
        inputs = read_inputs();

        if (inputs.up && get_snake()->direction != DOWNWARD) {
            get_snake()->direction = UPWARD;
        } else if (inputs.down && get_snake()->direction != UPWARD) {
            get_snake()->direction = DOWNWARD;
        } else if (inputs.left && get_snake()->direction != RIGHT) {
            get_snake()->direction = LEFT;
        } else if (inputs.right && get_snake()->direction != LEFT) {
            get_snake()->direction = RIGHT;
        }

        // 6. Move the snake (only on certain ticks to control speed)
        if (tick % TICK_RATE == 0) {
            // Move snake every TICK_RATE ticks (no special speed for boosted mode)
            move_snake();
        }
        
        // Decrease boost timer if active
        if (get_snake()->boosted > 0) {
            get_snake()->boosted--;
        }
        
        tick++;
        t.reset();
    }

    // Wait for button press to restart game
    if (game_over) {
        while(1) {
            inputs = read_inputs();
            if (inputs.up || inputs.down || inputs.right || inputs.left || inputs.center || inputs.b1 || inputs.b2 || inputs.b3) {
                goto game_start;
            }
        }
    }

    printf("out of main loop\n");
    cleanupGame();

    return 0;
}

// Function to clean up game resources
void cleanupGame() {
    if (get_snake() != NULL && get_snake()->snake_list != NULL) {
        destroyList(get_snake()->snake_list);
        free(get_snake());
    }
    
    if (get_items() != NULL && get_items()->items_list != NULL) {
        destroyList(get_items()->items_list);
        free(get_items());
    }
}
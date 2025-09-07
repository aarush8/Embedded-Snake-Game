// ============================================
// The Snake class file
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================


#include "snake.h"
#include "doubly_linked_list.h"
#include "hardware.h"
#include "globals.h" // Added to get point type definition and CELL_SIZE
#include <string>
#include <typeinfo>
#include "graphics.h"

// Define screen dimensions based on CELL_SIZE from globals.h
#define SIZE_X 128
#define SIZE_Y 128

Snake* snake;
DLinkedList* SnakeDLL = NULL;

// 2035TODO
// This function should initialize the Snake struct and populate its linked list with 10 SnakeItems.
void snake_init()
{
    // Allocate memory for the Snake structure
    snake = (Snake*)malloc(sizeof(Snake));
    
    // Initialize the snake properties
    snake->direction = RIGHT;
    snake->length = 10;
    snake->score = 0;
    snake->boosted = 0;
    
    // Create a new doubly linked list for the snake
    SnakeDLL = create_dlinkedlist();
    snake->snake_list = SnakeDLL;
    
    // Populate the linked list with 10 SnakeItems (starting at the center and going left)
    int center_x = SIZE_X / (2 * CELL_SIZE);
    int center_y = SIZE_Y / (2 * CELL_SIZE);
    
    // Create snake head
    SnakeItem* head = (SnakeItem*)malloc(sizeof(SnakeItem));
    head->position.x = center_x;
    head->position.y = center_y;
    head->draw = draw_snake_head;
    head->data = NULL;
    insertHead(SnakeDLL, head);
    
    // Create rest of the snake body (9 more segments)
    for (int i = 1; i < snake->length; i++) {
        SnakeItem* body = (SnakeItem*)malloc(sizeof(SnakeItem));
        body->position.x = center_x - i; // Each segment is to the left of the previous one
        body->position.y = center_y;
        body->draw = draw_snake_body;
        body->data = NULL;
        insertTail(SnakeDLL, body);
    }
    
    // Initialize the previous tail position
    LLNode* tail_node = getTail(SnakeDLL);
    SnakeItem* tail_item = (SnakeItem*)getData(tail_node);
    snake->previous_tail_position = tail_item->position;
}

// 2035TODO
// This function updates the location of the SnakeItems in the Snake's DLL
void move_snake() {
    // Get the head node and its data
    LLNode* head_node = getHead(SnakeDLL);
    SnakeItem* head_item = (SnakeItem*)getData(head_node);
    
    // Get the tail node and its data for tracking previous position
    LLNode* tail_node = getTail(SnakeDLL);
    SnakeItem* tail_item = (SnakeItem*)getData(tail_node);
    
    // Store the previous tail position before moving
    snake->previous_tail_position = tail_item->position;
    
    // Clear the previous tail position on screen
    draw_nothing(snake->previous_tail_position.x, snake->previous_tail_position.y);
    
    // Calculate new head position based on direction
    point new_head_position = head_item->position;
    switch(snake->direction) {
        case RIGHT:
            new_head_position.x++;
            break;
        case LEFT:
            new_head_position.x--;
            break;
        case UPWARD:
            new_head_position.y--;
            break;
        case DOWNWARD:
            new_head_position.y++;
            break;
        default:
            break; // No movement if NONE
    }
    
    // Move all body segments to the position of the segment in front of them
    // Start from the tail and move each segment to the position of the one before it
    LLNode* current = tail_node;
    while (current != head_node) {
        LLNode* prev_node = getPrev(current);
        if (prev_node != NULL) {
            SnakeItem* current_item = (SnakeItem*)getData(current);
            SnakeItem* prev_item = (SnakeItem*)getData(prev_node);
            
            // Move the current segment to the position of the segment in front
            current_item->position = prev_item->position;
        }
        current = prev_node;
    }
    
    // Update the head position to the new position
    head_item->position = new_head_position;
}

// 2035TODO
// This function should check if the Snake has collided with a wall, returns 1 on collision
// Note that the left and top of the uLCD are x=0 and y=0, respectively
// The right and bottom of the screen are SIZE_X/CELL_SIZE and SIZE_Y/CELL_SIZE, respectively
bool check_wall_collision() {
    // Get the head position
    LLNode* head_node = getHead(SnakeDLL);
    SnakeItem* head_item = (SnakeItem*)getData(head_node);
    point head_pos = head_item->position;
    
    // Check if the head has hit the boundaries
    if (head_pos.x < 0 || head_pos.x >= SIZE_X/CELL_SIZE ||
        head_pos.y < 0 || head_pos.y >= SIZE_Y/CELL_SIZE) {
        return true;
    }
    
    return false;
}


// 2035TODO
// This function should check if the Snake has collided with itself, returns 1 on collision
bool check_self_collision() {
    // Get the head position
    LLNode* head_node = getHead(SnakeDLL);
    SnakeItem* head_item = (SnakeItem*)getData(head_node);
    point head_pos = head_item->position;
    
    // Check each body segment (starting from the second segment)
    LLNode* current = getNext(head_node);
    while (current != NULL) {
        SnakeItem* current_item = (SnakeItem*)getData(current);
        
        // If the head position matches any body segment position, collision occurred
        if (head_pos.x == current_item->position.x && 
            head_pos.y == current_item->position.y) {
            return 1;
        }
        
        current = getNext(current);
    }
    
    return 0;
}

// 2035TODO
// This function should increase the physical length of the Snake.
void grow_snake()
{
    // Create new body segment
    SnakeItem* new_body = (SnakeItem*)malloc(sizeof(SnakeItem));
    
    // Set the position to the previous tail position
    new_body->position = snake->previous_tail_position;
    new_body->draw = draw_snake_body;
    new_body->data = NULL;
    
    // Add new segment to the end of the snake
    insertTail(SnakeDLL, new_body);
    
    // Increment the snake's length
    snake->length++;
}

// 2035TODO
// This function should draw all the SnakeItems in the Snake linked list
void draw_snake(void) {
    LLNode* current = getHead(SnakeDLL);
    
    while (current != NULL) {
        SnakeItem* item = (SnakeItem*)getData(current);
        // Call the draw function for this item
        item->draw(item->position.x, item->position.y);
        current = getNext(current);
    }
}

Snake* get_snake(void) {
    return snake;
}

point get_snake_head_location(void) {
    LLNode* head = SnakeDLL->head;
    return ((SnakeItem*)head->data)->position;
}



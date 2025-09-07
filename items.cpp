// ============================================
// The Items class file
//
// Copyright 2025 Georgia Tech. All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must NOT be made publicly available anywhere.
//==================================================================



#include "items.h"
#include "snake.h"
#include "globals.h"
#include "graphics.h"
#include "doubly_linked_list.h"
#include <cstdlib>
#include <ctime>


Items* items;

// 2035TODO
// This function should initialize the Items struct and populate its linked list with 10 Item.
void items_init(void)
{
    // Allocate memory for the Items struct
    items = (Items*)malloc(sizeof(Items));
    if (items == NULL) {
        return;
    }
    
    // Create the items linked list
    items->items_list = create_dlinkedlist();
    items->data = NULL;

    Snake* snake = get_snake();
    srand(time(NULL));

    // Create 10 items at random positions
    for (int i = 0; i < NUM_ITEMS; i++) {
        // Allocate memory for a new item using C-style allocation
        Item* new_item = (Item*)malloc(sizeof(Item));
        if (new_item == NULL) {
            continue;  // Skip this iteration if memory allocation fails
        }
        
        // Initialize the new item's data field
        new_item->data = NULL;
        
        bool valid_position = false;

        do {
            new_item->position.x = rand() % (SIZE_X / CELL_SIZE);
            new_item->position.y = rand() % (SIZE_Y / CELL_SIZE);

            bool overlap = false;
            
            // Check overlap with snake segments
            for (LLNode* sNode = snake->snake_list->head; sNode != NULL; sNode = sNode->next) {
                SnakeItem* seg = (SnakeItem*)sNode->data;
                if (seg->position.x == new_item->position.x && seg->position.y == new_item->position.y) {
                    overlap = true;
                    break;
                }
            }

            // Check overlap with existing items
            if (!overlap) {
                for (LLNode* iNode = items->items_list->head; iNode != NULL; iNode = iNode->next) {
                    Item* existing = (Item*)iNode->data;
                    if (existing->position.x == new_item->position.x && existing->position.y == new_item->position.y) {
                        overlap = true;
                        break;
                    }
                }
            }

            valid_position = !overlap;
        } while (!valid_position);

        // Randomly assign an item type
        new_item->type = rand() % 3;

        // Set the draw function based on the item type
        switch(new_item->type) {
            case FRUIT:
                new_item->draw = draw_fruit;
                break;
            case BOOST:
                new_item->draw = draw_boost;
                break;
            case POISON:
                new_item->draw = draw_poison;
                break;
        }

        insertTail(items->items_list, new_item);
    }
}

//2035 TODO
// This function should check if the snake's head collides with any items and handle each possible collision accordingly
// Should return 1 for a GAME-ENDING collision, 0 otherwise
bool check_item_collision() {
    // If an item is eaten, it should be replaced at a new location
    Snake* snake = get_snake();
    Items* items_obj = get_items();
    
    // Get the snake's head position
    LLNode* head_node = snake->snake_list->head;
    SnakeItem* head_item = (SnakeItem*)head_node->data;
    point head_pos = head_item->position;
    
    // Check collision with each item
    LLNode* current = items_obj->items_list->head;
    
    while (current != NULL) {
        Item* item = (Item*)current->data;
        
        // Check if the head position matches the item position
        if (head_pos.x == item->position.x && head_pos.y == item->position.y) {
            // Handle collision based on item type
            switch(item->type) {
                case FRUIT:
                    // Increase score and grow snake
                    if (snake->boosted > 0) {
                        // Double points when boosted
                        snake->score += 2;
                    } else {
                        snake->score++;
                    }
                    grow_snake();
                    break;
                    
                case BOOST:
                    // Apply boost effect for a limited time
                    snake->boosted = 10; // Set boost timer for 10 ticks
                    break;
                    
                case POISON:
                    // Reduce score by 1 instead of ending game
                    if (snake->score > 0) {
                        snake->score--;
                    }
                    break;
            }
            
            // Replace the item
            LLNode* temp = current;
            current = current->next; // Move to the next node before replacing
            replace_item(temp);
            continue; // Skip the current increment since we've already moved current
        }
        
        current = current->next;
    }
    
    return false; // No game-ending collision
}

// This function should delete and replace an item that was eaten by the snake
void replace_item(LLNode* current_item) {
    if (!current_item || !current_item->data) {
        return;
    }
    
    Items* items_obj = get_items();
    Snake* snake = get_snake();
    Item* old_item = (Item*)current_item->data;
    Item* new_item = (Item*) malloc(sizeof(Item));
    
    if (!new_item) {
        return; // Memory allocation failed
    }
    
    // Generate a new random position that doesn't overlap with the snake or other items
    bool valid_position = false;
    
    do {
        new_item->position.x = rand() % (SIZE_X / CELL_SIZE);
        new_item->position.y = rand() % (SIZE_Y / CELL_SIZE);
        
        bool overlap = false;
        
        // Check overlap with snake
        LLNode* snake_node = snake->snake_list->head;
        while (snake_node != NULL) {
            SnakeItem* segment = (SnakeItem*)snake_node->data;
            if (segment->position.x == new_item->position.x && segment->position.y == new_item->position.y) {
                overlap = true;
                break;
            }
            snake_node = snake_node->next;
        }
        
        if (!overlap) {
            // Check overlap with other items
            LLNode* item_node = items_obj->items_list->head;
            while (item_node != NULL) {
                if (item_node != current_item) { // Skip the current item being replaced
                    Item* existing_item = (Item*)item_node->data;
                    if (existing_item->position.x == new_item->position.x && existing_item->position.y == new_item->position.y) {
                        overlap = true;
                        break;
                    }
                }
                item_node = item_node->next;
            }
        }
        
        valid_position = !overlap;
    } while (!valid_position);
    
    // Keep the same type or choose a new random type
    //new_item->type = rand() % 3;
    
    // Set the draw function based on the item type
    switch(new_item->type) {
        case FRUIT:
            new_item->draw = draw_fruit;
            break;
        case BOOST:
            new_item->draw = draw_boost;
            break;
        case POISON:
            new_item->draw = draw_poison;
            break;
    }
    
    new_item->data = NULL;
    
    // Replace the old item with the new one
    free(old_item);
    current_item->data = new_item;
}

// This function should draw all of the items in the Items linked list
void draw_items(void) {
    Items* items_obj = get_items();
    
    if (!items_obj || !items_obj->items_list) {
        return;
    }
    
    // Iterate through the items list and draw each item
    LLNode* current = items_obj->items_list->head;
    
    while (current != NULL) {
        Item* item = (Item*)current->data;
        
        // Call the item's draw function with its position
        if (item && item->draw) {
            item->draw(item->position.x, item->position.y);
        }
        
        current = current->next;
    }
}

Items* get_items(void) {
    return items;
}
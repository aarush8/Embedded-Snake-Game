// PASTE YOUR DLL CODE HERE
//=================================================================
// Implementation for DLL module.
//
// Copyright 2025 Georgia Tech.  All rights reserved.
// The materials provided by the instructor in this course are for
// the use of the students currently enrolled in the course.
// Copyrighted course materials may not be further disseminated.
// This file must not be made publicly available anywhere.
//=================================================================
#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list.h"

LLNode* create_llnode(void* data) {

    // Your code here
    LLNode* newNode = (LLNode*)malloc(sizeof(LLNode));

    if (newNode == NULL) {
      printf("Memory allocation error");
      return NULL;
    }

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;

}

DLinkedList* create_dlinkedlist(void) {
    DLinkedList* newList = (DLinkedList*)malloc(sizeof(DLinkedList));
    newList->head = NULL;
    newList->tail = NULL;
    newList->size = 0;
    return newList;
}


int getSize(DLinkedList* dLinkedList){
  // Your code here
  if (dLinkedList == NULL) {
     return 0;
  }
  return dLinkedList->size;
}


LLNode* getHead(DLinkedList* dLinkedList){
  // Your code here
  if (dLinkedList == NULL) {
     return NULL;
  }
  return dLinkedList->head;
}


LLNode* getTail(DLinkedList* dLinkedList){
  if (dLinkedList == NULL) {
     return NULL;
  }
  return dLinkedList->tail;
}


LLNode* getNext(LLNode* node){

  // Your code here
  if (node == NULL) {
    return NULL; // Or handle error as appropriate for your design
  }
  return node->next;

}

LLNode* getPrev(LLNode* node){

  // Your code here
  if (node == NULL) {
    return NULL;
  }
  return node->prev;

}

void* getData(LLNode* node){

  // Your code here
  if (node == NULL) {
    return NULL;
  }
  return node->data;

}

void insertAfter(DLinkedList* dLinkedList, LLNode* prev_node, void* data){
  if (prev_node == NULL) {
    printf("the given previous node cannot be NULL");
    return;
  }

  // Your code here
  LLNode* newNode = create_llnode(data);

  if (newNode == NULL) {
    return;
  }
  LLNode* nextNode = prev_node->next;

  newNode->next = nextNode;      // newNode points forward to the original next node
  newNode->prev = prev_node;     // newNode points back to prev_node

  prev_node->next = newNode;     // prev_node points forward to newNode

  if (nextNode != NULL) {
    nextNode->prev = newNode;  // The original next node points back to newNode
  }

  if (dLinkedList->tail == prev_node) {
    dLinkedList->tail = newNode;
  }

  dLinkedList->size++;

  return;
}

void insertBefore(DLinkedList* dLinkedList, LLNode* next_node, void* data){
  if (dLinkedList == NULL || next_node == NULL) {
    printf("the given next node cannot be NULL");
    return;
  }

  LLNode* newNode = create_llnode(data);
  if (newNode == NULL) {
    return;
  }

  newNode->next = next_node;
  newNode->prev = next_node->prev;
  if (newNode->prev != NULL) {
    newNode->prev->next = newNode;
  } else {
    dLinkedList->head = newNode;
  }

  next_node->prev = newNode;
  dLinkedList->size++;
}

void insertHead(DLinkedList* dLinkedList, void* data){
  if(dLinkedList->head == NULL){
    LLNode* newNode = create_llnode(data);
    dLinkedList->head = newNode;
    dLinkedList->tail = newNode;
    dLinkedList->size++; 
  }else{
    insertBefore(dLinkedList, dLinkedList->head, data);
    // return; // can you call a different method here instead? Do you need a return statement here?
  }
}

void insertTail(DLinkedList* dLinkedList, void* data){

  // Your code here
  if (dLinkedList == NULL) {
     return;
  }

  if (dLinkedList->tail == NULL) {
    insertHead(dLinkedList, data);
  } else {
    insertAfter(dLinkedList, dLinkedList->tail, data);
  }
}


void deleteNode(DLinkedList* dLinkedList, LLNode* Node){

  // Your code here
  if (dLinkedList == NULL || Node == NULL || dLinkedList->size == 0) {
      return;
  }

  LLNode* prevNode = Node->prev;
  LLNode* nextNode = Node->next;

  if (prevNode != NULL) {
      prevNode->next = nextNode;
  } else {
      dLinkedList->head = nextNode;
  }

  if (nextNode != NULL) {
      nextNode->prev = prevNode;
  } else {
      dLinkedList->tail = prevNode;
  }

  if (Node->data != NULL) {
      free(Node->data);
  }

  free(Node);

  dLinkedList->size--;
}


void destroyList(DLinkedList* dLinkedList){

  // Your code here
  // make sure you go through each node or else you wil get meemory leaks.
  if (dLinkedList == NULL) {
      return;
  }

  LLNode* current = dLinkedList->head;
  LLNode* nextNode;

  while (current != NULL) {
      nextNode = current->next;

      if (current->data != NULL) {
          free(current->data);
      }
      free(current);
      current = nextNode;
  }

  free(dLinkedList);
}


DLinkedList* split(DLinkedList* dLinkedList, LLNode* Node)
{

  // Your code here
  if (dLinkedList == NULL || Node == NULL || dLinkedList->size == 0) {
      return NULL;
  }

  if (Node == dLinkedList->tail) {
      return NULL;
  }

  DLinkedList* newList = create_dlinkedlist();
  if (newList == NULL) {
      return NULL;
  }

  LLNode* newHead = Node->next;

  newList->head = newHead;
  newList->tail = dLinkedList->tail;

  int count = 0;
  LLNode* temp = newHead;
  while (temp != NULL) {
      count++;
      temp = temp->next;
  }
  newList->size = count;

  dLinkedList->tail = Node;
  dLinkedList->size -= newList->size;

  Node->next = NULL;
  if (newHead != NULL) {
      newHead->prev = NULL;
  }

  return newList;
}


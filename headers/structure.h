#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "card.h"


typedef struct card stack_elm;

/*Defining the stack type */
typedef struct elm* stack;

/* Defining a stack elm */
typedef struct elm {
    stack_elm val;
    stack next;
} elm;

/*
* @brief creates a new empty stack and allocates memory
* @return an empty stack
*/
stack create_stack();

/*
*@brief check if the stack is empty or not
*@return 1 is the stack is empty, else 0
*/
int is_empty_stack(stack);

/*
*@brief modify the stack by pushing an element at the beginning
*
*/
void push_stack(stack_elm, stack*);

/* 
*@brief removes the first element of the stack 
*@return the first element which has been removed
*/
stack_elm pop_stack(stack*);

/*
*@brief modify the stack by pushing an element at the end 
*
*/
void push_last_stack(stack_elm, stack *);

/*
*@brief removes the last element of the stack
*@return the last element which has been removed
*/
stack_elm pop_last_stack(stack*);

/*
*@brief find the position of the element in the stack
*@return an int defining the position of the element
*/
stack_elm get_stack_elem_position(elm , stack);

/*
*@brief computes the length of the stack
*@return the length of the stack
*/
int len_stack(stack);

/*
*brief print the stack [elem 1] ->[elem 2] -> [elem 3] -> ... -> []
*
*/
void print_stack(stack);

#endif
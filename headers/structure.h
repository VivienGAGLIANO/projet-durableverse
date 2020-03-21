#ifndef _STRUCTURE_H
#define _STRUCTURE_H

/*Defining the stack type */
typedef struct elm* stack;

/* Defining a stack elm */
type struct elm {
    int val;
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
void push_stack(int, stack*);

/* 
*@brief removes the first element of the stack 
*@return the first element which has been removed
*/
int pop_stack(stack*);

/*
*@brief modify the stack by pushing an element at the end 
*
*/
void push_last_stack(int, stack *);

/*
*@brief removes the last element of the stack
*@return the last element which has been removed
*/
int pop_last_stack(stack*);

/*
*@brief find the position of the element in the stack
*@return an int defining the position of the element
*/
int get_stack_elem_position(elem , stack);

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

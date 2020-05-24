#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "card.h"
#include "board.h"
#include "colors_logo.h"

/**
 * @brief prints the hand
 * @details displays the given card list as a hand, in the format of a list with : card index in hand list, name of the card and energy cost.
 * @param cards the card_list to print as a hand
 */
void print_hand(card_list cards);

/**
 * @brief prints new turn information 
 * @details prints turn number and each player's Sustainable Development (SD) points, states if new staff space is available and if FISA appear/disappear this turn
 * @param board the game board
 */
void print_new_turn(struct board board);

/**
 * @brief prints new phase information
 * @details states which player's turn it is, prints the board (student cards, staff cards, and SD points of each player) as well as the current player's hand
 * @param board the game board
 * @param current_player the player which is currently playing
 */
void print_new_phase(struct board board, struct ensiie current_player);

/**
 * @brief prints the current board
 * @details prints each player's SD points, student card number (FISE and FISA), staff card (by order played) and hand size
 * @param board the current board
 */
void print_board(struct board board);

/**
 * @brief asks player which student cards he desires
 * @details asks which student cards (FISE or FISA) are wanted, in accordance with the number of student card available for this player (computed using nb_student_card_received function)
 * If only one available, asks between FISE and FISA
 * Else asks how many of each, and verifies that the sum equals number of student cards available
 * Result is stored in given nb_FISE and nb_FISA variables
 * @param nb_FISE a pointer to an int in which will be stored the number of FISE the player wants
 * @param nb_FISA a pointer to an int in which will be stored the number of FISA the player wants
 * @param p the player which is currently playing
 * @pre nb_FISE and nb_FISA have to be allocated
 * @post *nb_FISE and *nb_FISA are updated
 */
void choice_FISE_FISA(int *nb_FISE, int *nb_FISA, struct ensiie p);

/**
 * @brief splits the given string in several pieces of size size
 * @param string the string to split
 * @param size the size of each chunk (except the last one which may be smaller)
 * @return a char** in which the chunks are stored
 */
char** split_string(char* string, int size);

/**
 * @brief display the given card in terminal ascii art
 * @details the card with given dimension will be printed with its name, cost, and effect in an ascii art card structure
 * @param card the card to display
 * @param width the width of the card, meaning the size of its longest character string
 */
void display_card(card card, int width);

/**
 * @brief asks the player to play a card or end his phase
 * @details Checks if chosen card's cost doesn't exceed available Energy Point (EP), and asks again with error message if it does. Returns the index of the card chosen in the hand of the player.
 * @param board the game board
 * @param p the ensiie which is currently playing
 * @param EP the current available EP of the player
 * @return the index of the card chosen in player's hand, or -1 if the player wants to end his turn
 */
int choice_card(struct board board, struct ensiie p, int EP);

/**
 * @brief prints the winner or draw, depending on the result of the game
 * @param board the game board
 * @pre game must be over for the function to run, i.e. function is_over must return true
 */
void print_end_game(struct board board);

/**
 * @brief prints Durableverse logo and group name
 */
void print_logo();

/**
 * @brief clears console
 */
void clear_screen();

/**
 * @brief prints Durableverse logo and asks user for each player's name
 * @param name1 name of the first player
 * @param name2 name of the second player
 * @post name1 and name2 are updated with the names entered by each player
 */
void welcome_screen(char* name1, char* name2);


#endif
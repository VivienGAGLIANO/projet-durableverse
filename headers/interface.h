#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "card.h"
#include "board.h"
#include "colors_logo.h"

/**
 * @brief prints the hand
 * @details displays the given card list as a hand, in the format of a list with : card index in hand list, name of the card and energy cost.
 */
void print_hand(card_list cards);

/**
 * @brief prints new turn information 
 * @details prints turn number and each player's Sustainable Development (SD) points, states if new staff space is available and if FISA appear/disappear this turn
 */
void print_new_turn(struct board);

/**
 * @brief prints new phase information
 * @details states which player's turn it is, prints the board (student cards, staff cards, and SD points of each player) as well as the current player's hand
 * 
 */
void print_new_phase(struct board, struct ensiie);

/**
 * @brief prints the current board
 * @details prints each player's SD points, student card number (FISE and FISA), staff card (by order played) and hand size
 */
void print_board(struct board);

/**
 * @brief asks player which student cards he desires
 * @details asks which student cards (FISE or FISA) are wanted, in accordance with the number of student card available for this player (computed using nb_student_card_received function)
 * If only one available, asks between FISE and FISA
 * Else asks how many of each, and verifies that the sum equals number of student cards available
 * Result is stored in given nb_FISE and nb_FISA variables
 */
void choice_FISE_FISA(int *nb_FISE, int *nb_FISA, struct ensiie);

/**
 * @brief asks the player to play a card or end his phase
 * @details Checks if chosen card's cost doesn't exceed available Energy Point (EP) (calls available_EP with given board), and asks again with error message if it does. Stores the return value in given chosen_card pointer
 * @return if a card is chosen, a pointer towards that card, NULL if end phase
 * @post chosen_card pointer is NULL if pass turn, else points towards chosen card
 */
int choice_card(struct board, struct ensiie);

/**
 * @brief prints the winner or draw, depending on the result of the game
 * @pre game must be over for the function to run, i.e. function is_over must return true
 */
void print_end_game(struct board);

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
#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "card.h"
#include "board.h"

/*
*@brief prints new turn information 
*@detail prints turn number and each player's Sustainable Development (SD) points, states if new staff space is available and if FISA appear/disappear this turn
*
*/
void print_new_turn(struct board);

/*
*@brief prints new phase information
*@detail states which player's turn it is, prints the board (student cards, staff cards, and SD points of each player) as well as the current player's hand
*
*/
void print_new_phase(struct board);

/*
*@brief prints the current board
*@detail prints each player's SD points, student card number (FISE and FISA), staff card (by order played) and hand size
*/
void print_board(struct board);

/*
*@brief asks player which student cards he desires
@detail asks which student cards (FISE or FISA) are wanted, in accordance with the number of student card available for this player (computed using nb_student_card_received function)
If only one available, asks between FISE and FISA
Else asks how many of each, and verifies that the sum equals number of student cards available
Result is stored in given nb_FISE and nb_FISA variables
*/
void choice_FISE_FISA(int *nb_FISE, int *nb_FISA, struct ensiie);

/*
*@brief asks the player to play a card or end his phase
*@detail Checks if chosen card's cost doesn't exceed available Energy Point (EP), and asks again with error message if not.
If if all cards in hand are unplayable, the only choice given is to end the phase
*@return if a card is chosen, a pointer towards that card, NULL if end phase
*/
struct card* choice_card(struct ensiie);

/*
*@brief prints the winner or draw, depending on the result of the game
*@pre game must be over for the function to run, i.e. function is_over must return true
*/
void print_end_game(struct board);


#endif
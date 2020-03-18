#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "card.h"
#include "board.h"

/*
*@brief checks the turn number and if it's even or odd
*@return turn number and if FISA appear or disappear and prints that a new one begin, prints if new staff space is available, Sustainale Development (SD) point of each players  
*/
void print_new_turn(struct board);

/*
*@brief checks the phase and the player
*@return the phase number, the player, print the board, and current player's hand
*/
void print_new_phase(struct board);

/*
* 
*@return prints the current board except the hand and the discard
*/
void print_board(struct board);

/*
*@detail ask how many student cards (FISE or FISA) wanted: if one is wanted, then ask which one, if more, the ask how many. 
Then check if the quantity wanted is available. The choice is savec in variant int FISE or int FISA
*/
void choice_FISE_FISA(int nb_FISE*, int nb_FISA*, struct ensiie);

/*
*@detail ask the player to play a hand card or to end the phase. Check if the cost < EP, if it's not then ask again with an error message.
If all hand card cost < EP then the only choice is to end the phase
@return prints EP, hand cards
*/
struct card choice_card(struct ensiie);

/*
*@return prints the winner or equality
*/
void print_end_game (struct board);


#endif
#ifndef _BOARD_H
#define _BOARD_H

#include "card.h"

#define MAX_CARD_NUMBER 50

/* -------------------------------------------------------- */
/* -------------------- Defining types -------------------- */
/* -------------------------------------------------------- */

/* General type for the staff cards currently on the board, and the maximum number of staff
 * cards allowed on the board
 */
struct board_staff {
    struct card* cards;
    int max;
};

/* General type for the students cards currently on the board (FISE and FISA),
 * the counter and the durability and development points for each type of student card
 */
struct board_students {
    int FISE_count;
    int FISA_count;
    int FISE_durability;
    int FISA_durability;
    int FISE_development;
    int FISA_development;
};

/* General type for one player (one ENSIIE), with its Sustainable Development points (int SD),
 * its deck, hand, and discard (which are lists/array of struct card), the current staff cards
 * and student cards currently on the board, and its opponent
 */
struct ensiie {
    int SD;
    struct card* deck;
    struct card hand[MAX_CARD_NUMBER];
    struct card* discard;
    struct board_staff current_staff;
    struct board_students current_students;
    struct ensiie* opponent_ensiie;
};

/* General type for the game board, including the two players and the turn counter
 */
struct board {
    struct ensiie player1;
    struct ensiie player2;
    int n_turn;
};


/* ------------------------------------------------------------ */
/* -------------------- Defining functions -------------------- */
/* ------------------------------------------------------------ */

/* 
 * @brief creates new board and allocates memory
 * @return initialized board instance 
 */
struct board new_board();

/* 
 * @brief frees memory taken by given board, including memory taken for both ensiie struct
 * 
 */
void free_board(struct board*);

/* 
 * @brief updates board state at the beginning of a new turn
 * @detail increments turn counter, handles FISA student cards turn based behaviour, updates number of space available for staff cards
 */
void begin_turn(struct board*);

/* 
 * @brief computes number of cards drawn by player
 * @return number of cards to be drawn
 */
int nb_card_drawn(struct ensiie);

/* 
 * @brief draws a card for the given player
 * 
 */
void draw(struct ensiie*);

/* 
 * @brief computes number of student cards received by the player
 * @return number of student cards to be received
 */
int nb_student_card_received(struct ensiie);

/* 
 * @brief adds given amount of FISE student cards to the player
 * 
 */
void add_student_FISE(int, struct ensiie*);

/* 
 * @brief adds given amount of FISA student cards to the player
 * 
 */
void add_student_FISA(int, struct ensiie*);

/* 
 * @brief computes Energy Points (EP) available at the beginning of the player's phase
 * @return number of EP available
 */
int available_EP(struct ensiie);

/*
 *@brief start a player's phase
 *
 */
void play_phase (struct ensiie*, int);

/* 
 * @brief allows player to play one card from its hand
 * @return 1 if card played, 0 if turn passed
 */
int play_card(struct ensiie*, int*);

/* 
 * @brief ends current turn, computes and updates Sustainable Development (SD) points for each player
 * 
 */
void end_turn(struct board*);

/* 
 * @brief checks if game is over, i.e. if winning condition of having 20+ Sustainable Development (SD) points is achieved
 * @return 1 if game is over, 0 else
 */
int is_over(struct board);


#endif
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
 * its deck, hand, and discard (which are lists/array of struct card), and the current staff cards
 * and student cards currently on the board
 */
struct ensiie {
    int SD;
    struct card* deck;
    struct card hand[MAX_CARD_NUMBER];
    struct card* discard;
    struct board_staff current_staff;
    struct board_students current_students;
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
 * 
 * 
 */
struct board new_board();

/* 
 * 
 * 
 */
void free_board(struct board*);

/* 
 * 
 * 
 */
void begin_turn(struct board*);

/* 
 * 
 * 
 */
int nb_card_drawn(struct ensiie);

/* 
 * 
 * 
 */
void draw(struct ensiie*);

/* 
 * 
 * 
 */
int nb_student_card_received(struct ensiie);

/* 
 * 
 * 
 */
void add_student_FISE(int, struct ensiie*);

/* 
 * 
 * 
 */
void add_student_FISA(int, struct ensiie*);

/* 
 * 
 * 
 */
int available_EP(struct ensiie);

/* 
 * 
 * 
 */
void play_card(struct ensiie*);

/* 
 * 
 * 
 */
void end_turn(struct board*);

/* 
 * 
 * 
 */
int is_over(struct board);


#endif
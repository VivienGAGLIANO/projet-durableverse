#ifndef _BOARD_H
#define _BOARD_H

#include "card.h"

#define MAX_CARD_NUMBER 50

/************ Defining types ************/
struct board_staff {
    struct card* cards;
    int max;
};
struct board_students {
    int FISE_count;
    int FISA_count;
    int FISE_durability;
    int FISA_durability;
    int FISE_development;
    int FISA_development;
};

struct ensiie {
    int DD;
    struct card* deck;
    struct card hand[MAX_CARD_NUMBER];
    struct card* discard;
    struct board_staff current_staff;
    struct board_students current_students;
};

struct board {
    struct ensiie player1;
    struct ensiie player2;
    int n_turn;
};



/************ Defining functions ************/

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
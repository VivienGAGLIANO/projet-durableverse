#ifndef _BOARD_H
#define _BOARD_H

#include "card.h"

/* -------------------------------------------------------- */
/* ------------------------- Types ------------------------ */
/* -------------------------------------------------------- */

/**
 * @brief General type for the staff cards currently on the board, and the maximum number of staff
 * cards allowed on the board
 */
struct board_staff {
    struct card* cards; /**< The staff cards currently on the ensiie's board */
    int max;            /**< The maximum number of staff cards of the ensiie's board at the same time */
};

/**
 * @brief General type for the students cards currently on the board (FISE and FISA),
 * the counter and the durability and development points for each type of student card
 */
struct board_students {
    int FISE_count;         /**< The number of FISE cards currenlty on the board */
    int FISA_count;         /**< The number of FISA cards currenlty on the board */
    int FISE_durability;    /**< Each FISE card's durabilty */
    int FISA_durability;    /**< Each FISA card's durabilty */
    int FISE_development;   /**< Each FISE card's development points */
    int FISA_development;   /**< Each FISA card's development points */
};

/**
 * @brief General type for one player (one ENSIIE), with its Sustainable Development points (int SD),
 * its deck, hand, and discard (which are lists/arrays of struct card), the current staff cards
 * and student cards currently on the board, and a pointer to its opponent
 */
struct ensiie {
    int SD;                 /**< The sustainable development points of the ensiie */
    struct card* deck;      /**< The deck */
    struct card* hand;      /**< The hand */
    struct card* discard;   /**< The discard */

    /** The current staff cards currently on the board */
    struct board_staff current_staff;

    /** The current student cards currently on the board */
    struct board_students current_students;

    /** A pointer to the opponent ensiie */
    struct ensiie* opponent;
};

/**
 * @brief General type for the game board, including the two players and the turn counter
 */
struct board {
    struct ensiie player1; /**< The first player */
    struct ensiie player2; /**< The second player */
    int n_turn; /**< The current turn number */
};


/* ------------------------------------------------------------ */
/* ------------------------- Functions ------------------------ */
/* ------------------------------------------------------------ */

/**
 * @brief creates new board and allocates memory
 * @return initialized board instance 
 */
struct board new_board();

/**
 * @brief frees memory taken by given board, including memory taken for both ensiie struct
 * 
 */
void free_board(struct board*);

/**
 * @brief updates board state at the beginning of a new turn
 * @detail increments turn counter, handles FISA student cards turn based behaviour, updates number of space available for staff cards
 */
void begin_turn(struct board*);

/**
 * @brief lets the ensiie to play his phase
 * @detail calculates the EP of the ensiie, how many FISA or FISE cards the ensiie wants to play, which action and staff cards the ensiie wants to play, and applies the effect of these cards
 * @param a pointer to the ensiie playing, and the turn number
 */
void play_phase(struct ensiie*, int);

/**
 * @brief computes number of cards drawn by player
 * @return number of cards to be drawn
 */
int nb_card_drawn(struct ensiie);

/**
 * @brief draws a card for the given player
 * 
 */
void draw(struct ensiie*);

/**
 * @brief computes number of student cards received by the player
 * @return number of student cards to be received
 */
int nb_student_card_received(struct ensiie);

/**
 * @brief adds given amount of FISE student cards to the player
 * 
 */
void add_student_FISE(int, struct ensiie*);

/**
 * @brief adds given amount of FISA student cards to the player
 * 
 */
void add_student_FISA(int, struct ensiie*);

/**
 * @brief computes Energy Points (EP) available at the beginning of the player's phase
 * @return number of EP available
 */
int available_EP(struct ensiie);

/**
 * @brief allows player to play one card from its hand
 * @param the ensiie which is playing, and the EP 
 * @return 1 if card played, 0 if turn passed by user
 */
int play_card(struct ensiie*, int* ep);

/**
 * @brief ends current turn, computes and updates Sustainable Development (SD) points for each player
 * 
 */
void end_turn(struct board*);

/**
 * @brief checks if game is over, i.e. if winning condition of having 20+ Sustainable Development (SD) points is achieved
 * @return 1 if game is over, 0 else
 */
int is_over(struct board);



/* ------------------------------------------------------------ */
/* ---------------------- Maybe unused ------------------------ */
/* ------------------------------------------------------------ */


/** 
 * @brief give the ensiie's deck
 * @return a pointer towards the ensiie deck
 */

//struct card* get_ensiie_deck(struct ensiie);

/** 
 * @brief give the ensiie's deck
 * @return a table which contain all the card in the ensiie's hand
 */

//struct card* get_ensiie_hand(struct ensiie);

/*
 * @brief give the ensiie's deck
 * @return a pointer towards the ensiie's discard
 */

//struct card* get_ensiie_discard(struct ensiie);

/*
 * @brief tell if the turn is even or not 
 * @return 1 if the turn is even, else 0
 */
int is_even(struct board);


#endif
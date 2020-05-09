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
    /** The staff cards currently on the ensiie's board */
    card_list cards;

    /** The maximum number of staff cards of the ensiie's board at the same time */
    int max;
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
 * @brief General type for one player (one ENSIIE), with its Sustainable Development points (int SD), its player name (char*)
 * its deck, hand, and discard (which are lists/arrays of struct card), the current staff cards
 * and student cards currently on the board, and a pointer to its opponent
 */
struct ensiie {
    /** The sustainable development points of the ensiie */
    int SD;

    /** The player name */
    char* player_name;

    /** The deck */
    card_list deck;

    /** The hand */
    card_list hand;

    /** The discard */
    card_list discard;

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
    /** The first player */
    struct ensiie player1;

    /** The second player */
    struct ensiie player2;
    
    /** The current turn number */
    int n_turn;
};


/* ------------------------------------------------------------ */
/* ------------------------- Functions ------------------------ */
/* ------------------------------------------------------------ */

/**
 * @brief creates new board and allocates memory
 * @param name1 the name of the first player
 * @param name2 the name of the second player
 * @return a pointer towards an initialized board instance 
 */
struct board* new_board(char* name1, char* name2);

/**
 * @brief frees memory taken by given board, including memory taken for both ensiie struct
 * @param b a pointer to the board to free memory of
 */
void free_board(struct board* b);

/**
 * @brief updates board state at the beginning of a new turn
 * @details increments turn counter, handles FISA student cards turn based behaviour, updates number of space available for staff cards
 * @param b a pointer to the board
 */
void begin_turn(struct board* b);

/**
 * @brief lets the ensiie to play his phase
 * @details calculates the EP of the ensiie, how many FISA or FISE cards the ensiie wants to play, which action and staff cards the ensiie wants to play, and applies the effect of these cards
 * @param board the current board
 * @param p a pointer to the ensiie currently playing
 */
void play_phase(struct board board, struct ensiie* p);

/**
 * @brief computes number of cards drawn by player at the beginning of his turn
 * @param p the player to compute the number of cards drawn by
 * @return number of cards to be drawn
 */
int nb_card_drawn(struct ensiie p);

/**
 * @brief draws a card for the given player
 * @param p a pointer to the player
 */
void draw(struct ensiie* p);

/**
 * @brief computes number of student cards received by the player at the beginning of his turn 
 * @param p the player
 * @return number of student cards to be received
 */
int nb_student_card_received(struct ensiie p);

/**
 * @brief adds given amount of FISE student cards to the player
 * @param nb number of FISE students to add
 * @param p a pointer to the ENSIIE to add students to
 */
void add_student_FISE(int nb, struct ensiie* p);

/**
 * @brief adds given amount of FISA student cards to the player
 * @param nb number of FISA students to add
 * @param p a pointer to the ENSIIE to add students to
 */
void add_student_FISA(int nb, struct ensiie* p);

/**
 * @brief computes Energy Points (EP) available at the beginning of the player's phase
 * @param board the game board
 * @param p the player to compute the available EP of
 * @return number of EP available
 */
int available_EP(struct board board, struct ensiie p);

/**
 * @brief plays one card from a player's hand, then updates his EPs and apply the effect of the card immediately if it's an action card
 * @param p a pointer to the ensiie which is playing
 * @param ep a pointer to the current EP of the player
 * @param card_index the index of the card the player wants to play in its hand
 * @pre the given card should be playable, i.e. its cost should be less than or equal to available EP
 * @return 1 if card played, 0 else
 */
int play_card(struct ensiie *p, int *ep, int card_index);

/**
 * @brief computes amount of development a player has, taking into account action and staff cards effect owned by both the player and its opponent
 * @param board the game board
 * @param p the player
 * @return development count for the given player
 */
int compute_development(struct board board, struct ensiie p);

/**
 * @brief computes amount of durability a player has, taking into account action and staff cards effect owned by both the player and its opponent
 * @param board the game board
 * @param p the player
 * @return durability count for the given player
 */
int compute_durability(struct board board, struct ensiie p);

/**
 * @brief ends current turn, computes and updates Sustainable Development (SD) points for each player
 * @param board a pointer to the game board
 */
void end_turn(struct board *board);

/**
 * @brief checks if game is over, i.e. if winning condition of having 20+ Sustainable Development (SD) points is achieved
 * @param b the game board
 * @return 1 if game is over, 0 else
 */
int is_over(struct board b);

/**
 * @brief tell if the turn is even or not 
 * @param b the game board
 * @return 1 if the turn is even, else 0
 */
int is_turn_even(struct board b);

/**
 * @brief tells if new staff emplacement is available this turn
 * @param b the game board
 * @return 1 if turn-1 is multiple of 5, 0 else
 */
int new_staff_available(struct board b);


#endif
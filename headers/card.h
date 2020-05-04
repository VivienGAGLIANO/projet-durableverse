#ifndef _CARD_H
#define _CARD_H

#include "structure.h"
#include "board.h"
#include "../lib/ezxml/ezxml.h"

/* ------------------------ Staff card ------------------------ */
/**
 * @brief enumeration for staff card effects
 */
enum staff_effect_id {AE1, AE2, AA1, AA2, RE1, RE2, RA1, RA2, ADD, RDD, DR, E}; 

/**
 * @brief staff card struct: composed of the effect of the card, as well as its "effectiveness"
 */
typedef struct staff_effect staff_effect;
struct staff_effect {
    enum staff_effect_id id; /**< The effect ID of the card */
    int value; /**< The value applied to the effect */
};


/* ------------------------ Action card ----------------------- */
/**
 * @brief enumeration for action card effects
 */
enum action_effect {WinOneSD = 1, DrawOneCard, PlayOneFISE, PlayOneFISA, Win6EP, RemoveOneFISEFISA, DiscardOneStaff, ShuffleDiscardDraw, IncreaseDevelopment, IncreaseDurability, RemoveAllFISEFISA};


/* ------------------------ General card ----------------------- */
enum card_type {STAFF_CARD, ACTION_CARD};
/**
 * @brief general card type definition, for action and staff cards. Includes card's name, cost, and two pointers (one of which will be NULL) poiting towards the effect of the card, being action or staff
 */
typedef struct card card;
struct card {
    char* name; /**< The name of the card */
    int cost; /**< The EP cost of the card */
    effect_list staff_effect; /**< The effects of the card if it is a staff card, the NULL pointer otherwise */
    enum action_effect action_effect; /**< The effects of the card if it is a action card, the NULL pointer otherwise */
};

/* --------------------- Functions for cards creation -------------------- */

enum staff_effect_id convert_staff_fx_id(const char* fx_id);

card_list load_cards(char* filename);

card create_staff_card(char* name, int cost);

void add_staff_card_effect(card* card, staff_effect fx);

card create_action_card(char* name, int cost, enum action_effect fx);


/* ------------------------ Functions for the game ----------------------- */

/**
 * @brief gives the EP cost of a card
 * @return EP cost of a card
 */
int EP_cost(struct card);

/**
 * @brief tells if a card is a staff card or an action card
 * @param
 * @return STAFF_CARD if it's a staff car and ACTION_CARD if it's an action card
 */
enum card_type type_of_card(struct card);

/**
 * @brief quantity of card in the deck at the beginning
 * @return the number of same card in the deck at the beginning
 */
int nb_card_deck(struct card);

/**
 * @brief quantity of this type of staff card in the player board
 * @return the number of same card in the player1 board when the player1 start playing
 */

int nb_card_board(struct ensiie, struct card);

/**
 * @brief quantity of this type of staff card in the ennemy player board
 * @return the number of same card in the player2 board when the player1 start playing
 */

int nb_card_ennemy_board(struct ensiie, struct card);
 


#endif
#include "structure.h"

#ifndef _CARD_H
#define _CARD_H

#include "../lib/ezxml/ezxml.h"

/* ------------------------ Staff card ------------------------ */
/**
 * @brief enumeration for staff card effects
 */
enum staff_effect_id {AE1, AE2, AA1, AA2, RE1, RE2, RA1, RA2, ADD, RDD, DR, E}; 

/**
 * @brief staff card struct: composed of the effect of the card, as well as its "effectiveness" and a short description
 */
typedef struct staff_effect staff_effect;
struct staff_effect {
    /** The effect ID of the card */
    enum staff_effect_id id;

    /** The value applied to the effect */
    int value;

    /** Description of the effect */
    char* desc;
};


/* ------------------------ Action card ----------------------- */
/**
 * @brief enumeration for action card effects
 */
enum action_effect {WinOneSD, DrawOneCard, PlayOneFISE, PlayOneFISA, Win6EP, RemoveOneFISEFISA, DiscardOneStaff, ShuffleDiscardDraw, IncreaseDevelopment, IncreaseDurability, RemoveAllFISEFISA};


/* ------------------------ General card ----------------------- */
enum card_type {STAFF_CARD, ACTION_CARD};
/**
 * @brief general card type definition, for action and staff cards.
 * Includes card's type, name, cost, and :
 *  - the list of staff effects is the card is a staff card
 *  - the action effect and its description if the card is an action card
 */
typedef struct card card;
struct card {
    /** The type of the card (ACTION_CARD or STAFF_CARD) */
    enum card_type type;
    
    /** The name of the card */
    char* name;

    /** The EP cost of the card */
    int cost;

    /** The effects of the card if it is a staff card, an empty stack otherwise */
    effect_list staff_effect;

    /** The effects of the card if it is a action card, undefined otherwise */
    enum action_effect action_effect;

    /** Description of the action card effect (undefined if staff card) */
    char* desc;

};

/* --------------------- Functions for cards creation -------------------- */

/**
 * @brief converts a string of a staff effect id into an enumeration
 * @param fx_id the effect id, as a string
 * @return the corresponding `enum staff_effect_id` if the string is matched with an effect id, 0 otherwise
 */
enum staff_effect_id convert_staff_fx_id(const char* fx_id);

/**
 * @brief converts a string of an action effect id into an enumeration
 * @param fx_id the effect id, as a string
 * @return the corresponding `enum action_effect` if the string is matched with an effect id, 0 otherwise
 */
enum action_effect convert_action_fx(const char* fx_id);

/**
 * @brief replaces the character 'X' in the string `desc` with the int X
 * @param X the int to insert in the string to replace the character 'X'
 * @param *desc the string in which replace 'X' by given X value
 * @pre `desc` contains at least once the character 'X'
 * @return a pointer to the new string, with the character 'X' replaced by the int X
 */
char* format_effect_description(int X, char* desc);

/**
 * @brief loads cards in the XML file `filename`, and returns them as a card_list
 * @param filename the XML file in which to search for the cards
 * @pre the file has to be a valid XML file
 * @return a card_list of all the cards in `filename`
 */
card_list load_cards(char* filename);

/**
 * @brief creates a card
 * @param name the name of the card to be created
 * @param cost the cost of the card to be created
 * @return the newly created card
 */
card create_card(const char* name, int cost);

/**
 * @brief creates a staff card
 * @param name the name of the staff card to be created
 * @param cost the cost of the staff card to be created
 * @return the newly created staff card
 */
card create_staff_card(const char* name, int cost);

/**
 * @brief adds an effect to an existing staff card
 * @param card a pointer to the card to add effect to
 * @param fx the staff effect to add
 * @post the effect `fx` is added to the card `card`
 */
void add_staff_card_effect(card* card, staff_effect fx);

/**
 * @brief creates an action card
 * @param name the name of the action card to be created
 * @param cost the cost of the action card to be created
 * @param action_effect the action effect of the action card
 * @param desc a short description of the effect of the card
 * @return the newly created action card
 */
card create_action_card(const char* name, int cost, enum action_effect fx, const char* desc);


/* ------------------------ Functions for the game ----------------------- */

/**
 * @brief gives the EP cost of a card
 * @param card the card to get the cost of
 * @return the EP cost of a card
 */
int EP_cost(struct card card);

/**
 * @brief tells if a card is a staff card or an action card
 * @param card the card to get the type of
 * @return STAFF_CARD if it's a staff car and ACTION_CARD if it's an action card
 */
enum card_type type_of_card(struct card card);

/**
 * @brief gets all staff effects in a list of staff cards
 * @param cards the list of cards to get the effects of
 * @return an effect_list of all the effects of all the cards in `cards`
 */
effect_list get_all_staff_effects(card_list cards);


#endif
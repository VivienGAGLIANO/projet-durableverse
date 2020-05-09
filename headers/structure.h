#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "../lib/stack/stack.h"

typedef stack card_list;
typedef stack effect_list;

#include "../headers/card.h"

/* ------------ Cards functions ------------ */

/**
 * @brief pushes a card to a card_list
 * @details copies the card `card` with memcpy and adds it to the stack at the first place
 * @param card the card to push
 * @param list a pointer to the card list to add the card to
 */
void push_card(card card, card_list *list);

/**
 * @brief pops a card from the stack
 * @details removes the first card of the stack and returns it
 * @param list a pointer to the card list
 * @pre the list has to be non empty
 * @return the removed card
 */
card pop_card(card_list *list);

/**
 * @brief returns the index-th card of a list
 * @param list the card list
 * @param index the index of the card to get
 * @pre index < stack_len(list)
 * @return the index-th card in the stack
 */
card get_card(card_list list, int index);

/**
 * @brief removes a card from a list of cards and returns the element removed
 * @param list a pointer to the list to remove the card of
 * @param index the index of the card to remove
 * @pre index < stack_len(*list)
 * @post the index-th card is removed from the list
 * @return the card removed
 */
card remove_card(card_list *list, int index);

/**
 * @brief pops the last card of a list
 * @details removes the last card from a list of cards and returns it
 * @param list a pointer to the card list
 * @pre the stack has to be non-empty
 * @return the card removed
 */
card pop_last_card(card_list *list);


/* ------------ Effects functions ------------ */

/**
 * @brief pushes an effect to an effect_list
 * @details copies the effect `fx` with memcpy and adds it to the stack at the first place
 * @param fx the effect to push
 * @param list a pointer to the effect list to add the effect to
 */
void push_effect(staff_effect fx, effect_list *list);

/**
 * @brief pops an effect from the stack
 * @details removes the first effect of the stack and returns it
 * @param list a pointer to the effects list
 * @pre the list has to be non empty
 * @return the removed effect
 */
staff_effect pop_effect(effect_list *list);

/**
 * @brief returns the index-th effect of a list
 * @param list the effect list
 * @param index the index of the effect to get
 * @pre index < stack_len(list)
 * @return the index-th effect in the stack
 */
staff_effect get_effect(effect_list list, int index);

/**
 * @brief removes an effect from a list of effects and returns the element removed
 * @param list a pointer to the list to remove the effect of
 * @param index the index of the effect to remove
 * @pre index < stack_len(*list)
 * @post the index-th effect is removed from the list
 * @return the effect removed
 */
staff_effect remove_effect(effect_list *list, int index);

/**
 * @brief pops the last effect of a list
 * @details removes the last effect from a list of effects and returns it
 * @param list a pointer to the effects list
 * @pre the stack has to be non-empty
 * @return the effect removed
 */
staff_effect pop_last_effect(effect_list *list);


#endif
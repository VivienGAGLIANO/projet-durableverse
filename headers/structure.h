#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "../lib/stack/stack.h"
#include "../headers/card.h"

typedef stack card_list;
typedef stack effect_list;


/* ------------ Cards functions ------------ */

void push_card(card card, card_list *list);

card pop_card(card_list *list);

card get_card(card_list list, int index);

card remove_card(card_list *list, int index);


/* ------------ Effects functions ------------ */

void push_effect(staff_effect fx, effect_list *list);

staff_effect pop_effect(effect_list *list);

staff_effect get_effect(effect_list list, int index);

staff_effect remove_effect(effect_list *list, int index);


#endif
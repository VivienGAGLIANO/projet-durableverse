#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#include "../lib/stack/stack.h"

typedef stack card_list;
typedef stack effect_list;

#include "../headers/card.h"

/* ------------ Cards functions ------------ */

void push_card(card card, card_list *list);

card pop_card(card_list *list);

card get_card(card_list list, int index);

card remove_card(card_list *list, int index);

card pop_last_card(card_list *list);

/* ------------ Effects functions ------------ */

void push_effect(staff_effect fx, effect_list *list);

staff_effect pop_effect(effect_list *list);

staff_effect get_effect(effect_list list, int index);

staff_effect remove_effect(effect_list *list, int index);

staff_effect pop_last_effect(effect_list *list);

#endif
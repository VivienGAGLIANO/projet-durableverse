#include <stdlib.h>
#include "../headers/structure.h"

/* ------------ Cards functions ------------ */

void push_card(card card, card_list *list) {
	struct card* newcard = (struct card*) malloc(sizeof(struct card));
	memcpy(newcard, &card, sizeof(struct card));
	push(newcard, list);
}

card pop_card(card_list *list) {
	return *((card*) pop(list));
}

card get_card(card_list list, int index) {
	return *((card*) get_stack_elem(list, index));
}

card remove_card(card_list *list, int index) {
	return *((card*) pop_stack_elem(list, index));
}


/* ------------ Effects functions ------------ */

void push_effect(staff_effect fx, effect_list *list) {
	staff_effect* newfx = (staff_effect*) malloc(sizeof(staff_effect));
	memcpy(newfx, &fx, sizeof(struct staff_effect));
	push(newfx, list);
}

staff_effect pop_effect(effect_list *list) {
	return *((staff_effect*) pop(list));
}

staff_effect get_effect(effect_list list, int index) {
	return *((staff_effect*) get_stack_elem(list, index));
}

staff_effect remove_effect(effect_list *list, int index) {
	return *((staff_effect*) pop_stack_elem(list, index));
}

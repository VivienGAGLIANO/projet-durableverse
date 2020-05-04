#include "../headers/card.h"

/* --------------------- Functions for cards creation -------------------- */

enum staff_effect_id convert_staff_fx_id(const char* fx_id) {
	if (!strcmp(fx_id, "AE1")) return AE1;
	if (!strcmp(fx_id, "AE2")) return AE2;
	if (!strcmp(fx_id, "AA1")) return AA1;
	if (!strcmp(fx_id, "AA2")) return AA2;
	if (!strcmp(fx_id, "RE1")) return RE1;
	if (!strcmp(fx_id, "RE2")) return RE2;
	if (!strcmp(fx_id, "RA1")) return RA1;
	if (!strcmp(fx_id, "RA2")) return RA2;
	if (!strcmp(fx_id, "ADD")) return ADD;
	if (!strcmp(fx_id, "RDD")) return RDD;
	if (!strcmp(fx_id, "DR")) return DR;
	if (!strcmp(fx_id, "E")) return E;
}

card_list load_cards(char* filename) {
    ezxml_t xml_cards = ezxml_parse_file("cards.xml");
	card_list cards = create_stack();

    ezxml_t staff_cards = ezxml_child(xml_cards, "staffcards");
    for (ezxml_t card = ezxml_child(staff_cards, "card"); card; card = card->next) {
        const char* cardname = ezxml_child(card, "name")->txt;
        int card_id = atoi(ezxml_attr(card, "id"));
        int cost = atoi(ezxml_child(card, "cost")->txt);
        struct card newcard = create_staff_card(cardname, cost);
        for (ezxml_t effect = ezxml_child(card, "effect"); effect; effect = effect->next) {
            const char* effect_id = ezxml_attr(effect, "id");
            int value = atoi(ezxml_attr(effect, "value"));
			staff_effect fx = {convert_staff_fx_id(effect_id), value};
            add_staff_card_effect(&newcard, fx);
        }
        push_card(newcard, &cards);
    }

    ezxml_t action_cards = ezxml_child(xml_cards, "actioncards");
    for (ezxml_t card = ezxml_child(action_cards, "card"); card; card = card->next) {
        const char* cardname = ezxml_child(card, "name")->txt;
        int card_id = atoi(ezxml_attr(card, "id"));
        int cost = atoi(ezxml_child(card, "cost")->txt);
        int number = atoi(ezxml_child(card, "number")->txt);
        const char* desc = ezxml_child(card, "desc")->txt;
        // Here : create action card and add to the list
		/*struct card newcard = create_action_card(cardname, cost, ?); // comment trouver l'id ?
		push_card(newcard, &cards);*/
    }

    ezxml_free(xml_cards);
	return cards;
}

card create_card(char* name, int cost) {
	struct card newcard;
	newcard.name = name;
	newcard.cost = cost;
	newcard.staff_effect = NULL;
	newcard.action_effect = 0;
	return newcard;
}

card create_staff_card(char* name, int cost) {
	card newcard = create_card(name, cost);
	newcard.staff_effect = create_stack();
	return newcard;
}

void add_staff_card_effect(card* card, staff_effect fx) {
	push_effect(fx, &card->staff_effect);
}

card create_action_card(char* name, int cost, enum action_effect fx) {
	card newcard = create_card(name, cost);
	newcard.action_effect = fx;
	return newcard;
}



/* ------------------------ Functions for the game ----------------------- */
/**
 * @brief gives the EP cost of a card
 * @return the EP cost of a card
 */
int EP_cost(struct card a) {
	return a.cost;
}

/**
 * @brief tells if a card is a staff card or an action card
 * @param
 * @return STAFF_CARD if it's a staff car and ACTION_CARD if it's an action card
 */
int type_of_card(struct card a) {
	return a.action_effect ? ACTION_CARD : STAFF_CARD;
}

int nb_card_deck(struct card a){
	if type_of_card(a){
		if (*(a.action_effect)==(WinOneSD || DraweOneCard)) /* il y a 3 cartes "gagner un DD" et 3 cartes "piocher une carte" dans le deck en début de partie */
			return 3;
		else if (*(a.action_effect)==(PlayOneFISE || PlayOneFISA || Win6EP || RemoveOneFISEFISA)) /* il y a 2 cartes "jouer un Fisa", "jouer un FISE", "gagner 6 points d'énergie", "enlever une carte FISA OU FISE" dans le deck en début de partie*/
			return 2;
		else if (*(a.action_effect)== DiscardOneStaff)) /*il y a 4 carte "retirer une carte personnel" dans le deck au début*/
			return 4;
		else
			return 1;
	}
	else /* il y a une carte personnel de chaque type dans le deck au début*/
		return 1;
}

int nb_card_board(struct ensiie p, struct card a){
	int i = 0;
	while (not(is_empty_stack(p.current_staff.cards)))
	{
		if (p.current_staff.cards->val==a.name)
		{
			i+=1;
			p.current_staff.cards=p.current_staff.cards->next;
		}
		else
		{
			p.current_staff.cards=p.current_staff.cards->next;
		}
	return i;	
	}
}

int nb_card_ennemy_board(struct ensiie p, struct card a)
{
	int i = 0;
	while (not(is_empty_stack(p.opponent->current_staff.cards)))
	{
		if (p.opponent->current_staff.cards->val==a.name)
		{
			i+=1;
			p.opponent->current_staff.cards=p.current_staff.cards->next;
		}
		else
		{
			p.opponent->current_staff.cards=p.current_staff.cards->next;
		}
	return i;	
	}
}
#include <string.h>
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
	return 0;
}
enum action_effect convert_action_fx(const char* fx_id) {
	if (!strcmp(fx_id, "WinOneSD")) return WinOneSD;
	if (!strcmp(fx_id, "DrawOneCard")) return DrawOneCard;
	if (!strcmp(fx_id, "PlayOneFISE")) return PlayOneFISE;
	if (!strcmp(fx_id, "PlayOneFISA")) return PlayOneFISA;
	if (!strcmp(fx_id, "Win6EP")) return Win6EP;
	if (!strcmp(fx_id, "RemoveOneFISEFISA")) return RemoveOneFISEFISA;
	if (!strcmp(fx_id, "DiscardOneStaff")) return DiscardOneStaff;
	if (!strcmp(fx_id, "ShuffleDiscardDraw")) return ShuffleDiscardDraw;
	if (!strcmp(fx_id, "IncreaseDevelopment")) return IncreaseDevelopment;
	if (!strcmp(fx_id, "IncreaseDurability")) return IncreaseDurability;
	if (!strcmp(fx_id, "RemoveAllFISEFISA")) return RemoveAllFISEFISA;
	return 0;
}

card_list load_cards(char* filename) {
    ezxml_t xml_cards = ezxml_parse_file(filename);
	card_list cards = create_stack();

	char* effects_description[12];
	ezxml_t xml_fx = ezxml_parse_file("cards_effects.xml");
	for (ezxml_t fx = ezxml_child(xml_fx, "effect"); fx; fx = fx->next) {
		enum staff_effect_id id = convert_staff_fx_id(ezxml_child(fx, "id")->txt);
		const char* desc = ezxml_child(fx, "desc")->txt;
		effects_description[id] = (char*) desc;
	}

    ezxml_t staff_cards = ezxml_child(xml_cards, "staffcards");
    for (ezxml_t card = ezxml_child(staff_cards, "card"); card; card = card->next) {
        const char* cardname = ezxml_child(card, "name")->txt;
        //int card_id = atoi(ezxml_attr(card, "id"));
        int cost = atoi(ezxml_child(card, "cost")->txt);
		// Creating staff card...
        struct card newcard = create_staff_card(cardname, cost);
        for (ezxml_t effect = ezxml_child(card, "effect"); effect; effect = effect->next) {
            const char* effect_id = ezxml_attr(effect, "id");
            int value = atoi(ezxml_attr(effect, "value"));
			enum staff_effect_id id = convert_staff_fx_id(effect_id);
			staff_effect fx = {
				.id = id,
				.value = value,
				.desc = effects_description[id]
			};
            add_staff_card_effect(&newcard, fx);
        }
		// and adding it to the list
        push_card(newcard, &cards);
    }

    ezxml_t action_cards = ezxml_child(xml_cards, "actioncards");
    for (ezxml_t card = ezxml_child(action_cards, "card"); card; card = card->next) {
        const char* cardname = ezxml_child(card, "name")->txt;
        //int card_id = atoi(ezxml_attr(card, "id"));
        int cost = atoi(ezxml_child(card, "cost")->txt);
        int number = atoi(ezxml_child(card, "number")->txt);
        const char* desc = ezxml_child(card, "desc")->txt;
		const char* fx = ezxml_child(card, "effect")->txt;
        // Creating action card...
		struct card newcard = create_action_card(cardname, cost, convert_action_fx(fx), desc);
		// and adding it to the list
		for (int i = 0; i < number; i++)
			push_card(newcard, &cards);
    }

    ezxml_free(xml_cards);
	return cards;
}

card create_card(const char* name, int cost) {
	struct card newcard = {
		.name = (char*) malloc(sizeof(char)*(strlen(name)+1)),
		.cost = cost
	};
	strcpy(newcard.name, name);
	return newcard;
}

card create_staff_card(const char* name, int cost) {
	card newcard = create_card(name, cost);
	newcard.type = STAFF_CARD;
	newcard.staff_effect = create_stack();
	return newcard;
}

void add_staff_card_effect(card* card, staff_effect fx) {
	push_effect(fx, &card->staff_effect);
}

card create_action_card(const char* name, int cost, enum action_effect fx, const char* desc) {
	card newcard = create_card(name, cost);
	newcard.type = ACTION_CARD;
	newcard.action_effect = fx;
	newcard.desc = (char*) malloc(sizeof(char)*(strlen(desc)+1));
	strcpy(newcard.desc, desc);	
	return newcard;
}



/* ------------------------ Functions for the game ----------------------- */
/**
 * @brief gives the EP cost of a card
 * @param card the card to get the cost of
 * @return the EP cost of a card
 */
int EP_cost(struct card card) {
	return card.cost;
}

/**
 * @brief tells if a card is a staff card or an action card
 * @param card the card to get the type of
 * @return STAFF_CARD if it's a staff car and ACTION_CARD if it's an action card
 */
enum card_type type_of_card(struct card card) {
	return card.type;
}

/**
 * @brief quantity of card in the deck at the beginning
 * @return the number of same card in the deck at the beginning
 */
int nb_card_deck(struct card a){
	if (type_of_card(a) == ACTION_CARD) {
		switch (a.action_effect) {
			case WinOneSD:
			case DrawOneCard:
				/* il y a 3 cartes "gagner un DD" et 3 cartes "piocher une carte" dans le deck en début de partie */
				return 3;
				break;
			case PlayOneFISE:
			case PlayOneFISA:
			case Win6EP:
			case RemoveOneFISEFISA:
				/* il y a 2 cartes "jouer un Fisa", "jouer un FISE", "gagner 6 points d'énergie", "enlever une carte FISA OU FISE" dans le deck en début de partie */
				return 2;
				break;
			case DiscardOneStaff:
				/* il y a 4 carte "retirer une carte personnel" dans le deck au début */		
				return 4;
				break;
			default:
				return 1;
		}
	}
	else /* il y a une carte personnel de chaque type dans le deck au début*/
		return 1;
}

/**
 * @brief gets all staff effects in a list of staff cards
 * @param cards the list of cards to get the effects of
 * @return a effect_list of all the effects of all the cards in `cards`
 */
effect_list get_all_staff_effects(card_list cards) {
	effect_list effects = create_stack();
	for (int i = 0; i < stack_len(cards); i++) {
		effect_list card_effects = get_card(cards, i).staff_effect;
		for (int j = 0; j < stack_len(card_effects); j++) {
			push_effect(get_effect(card_effects, j), &effects);
		}
	}
	return effects;
}
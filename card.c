#include "card.h"
/*@ requires a a well-built card
	assigns nothing
	ensures return the cost of a
*/
int EP_cost(struct card a){
	return a.cost
}

/*@ requires a a well-built card
	assigns nothing
	ensures return 1 if a is an action card, o if it's a staff card
*/
int type_of_card(struct card a){
	if (a.staff_effect==NULL)
		return 1;
	else
		return 0;
}
/*@ requires a a well-built card
	assings nothing
	ensures return the amount of card similar to a in the deck in the begining of the game
*/
int nb_card_deck(struct card a){
	if type_of_card(a){
		if a.(*action_effect)==(WinOneSD || DraweOneCard)
			return 3;
		else if a.(*action_effect)==(PlayOneFISA || PlayOneFISA || Win6EP || RemoveOneFISEFISA)
			return 2;
		else if a.(*action_effect)== DiscardOneStaff
			return 4;
		else
			return 1;
	}
	else 
		return 1;
}


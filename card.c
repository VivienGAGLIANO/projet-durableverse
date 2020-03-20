#include "card.h"

int EP_cost(struct card a){
	return a.cost
}

int type_of_card(struct card a){
	if (a.staff_effect==NULL)
		return 1;
	else
		return 0;

}

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


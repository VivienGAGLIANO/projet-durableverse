#include "card.h"
#include "structure.h"
#include "board.h"

/*@ requires a a well-built card
	assigns nothing
	ensures return the cost of a
*/
int EP_cost(struct card a){
	return a.cost
}


int type_of_card(struct card a){
	if (a.staff_effect==NULL) /* si le pointeur staff_effect est NULL alors la carte est une carte action*/
		return 1;
	else
		return 0;
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
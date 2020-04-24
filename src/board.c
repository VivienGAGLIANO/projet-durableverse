#include "../headers/interface.h"
#include "../headers/board.h"


/**
 * @brief creates new board and allocates memory
 * @return initialized board instance 
 */
struct board new_board(){
	struct board board;
	return board;
}


/**
 * @brief frees memory taken by given board, including memory taken for both ensiie struct
 * 
 */
void free_board(struct board* b){
	free(b);
}

/**
 * @brief updates board state at the beginning of a new turn
 * @detail increments turn counter, handles FISA student cards turn based behaviour, updates number of space available for staff cards
 */
void begin_turn (struct board* board){
	interface.print_new_turn;
	board->n_turn+=1;
	if (is_peer(*b)) {
		board->player1.current_students.FISA_count=0;
		board->player2.current_students.FISA_count=0;
		board->player1.current_students.FISA_durability=0;
		board->player2.current_students.FISA_durability=0;
		board->player1.current_students.FISA_development=0;
		board->player2.current_students.FISA_development=0;
	}
	if ((board->n_turn-1)%5==0){
		board->player1.current_staff.max+=1;
		board->player2.current_staff.max+=1;
	}
	else if ((board->n_turn-1)%10==0){
		board->player1.current_staff.max+=2;
		board->player2.current_staff.max+=2;

	}
}

/**
 * @brief lets the ensiie to play his phase
 * @detail calculates the EP of the ensiie, how many FISA or FISE cards the ensiie wants to play, which action and staff cards the ensiie wants to play, and applies the effect of these cards
 * @param a pointer to the ensiie playing, and the turn number
 */
void play_phase(struct ensiie* ensiie, int turn_number){
	int energy_point;
	int *nb_FISE;
	int *nb_FISA;
	if (is_even(*board))
	{
		energy_point+= board->ensiie.current_students.FISE_count + 2*board->player1.current_students.FISA_count;
	}
	else
		energy_point+= board->ensiie.current_students.FISE_count;
	
	choice_FISE_FISA(nb_FISE, nb_FISA, *ensiie);
	choice_card(ensiie);
	
}

/**
 * @brief computes number of cards drawn by player
 * @return number of cards to be drawn
 */
int nb_card_drawn(struct ensiie ensiie){
	/*est ce utile?*/
	
}
/**
 * @brief draws a card for the given player
 * 
 */
void draw(struct ensiie*){
	card drawn_card=pop_card(&(ensiie.deck));
	push_card(card drawn_card, &(ensiie.hand));

}


int is_over(struct board b){
	if ((b.n_turn == 30) || b.player1.SD > 20 || b.player2.SD > 20)
		return 1;
	else
		return 0;
}

int is_even(struct board b){
	if ((b.n_turn)%2==0)
		return 1;
	else
		return 0;
}

void add_student_FISE(int a, struct ensiie* p){
	p->current_students.FISE_count+=a;
	p->current_students.FISE_development+=a;
	p->current_students.FISE_durability+=a;
}

void add_student_FISA(int a, struct ensiie* p){
	p->current_students.FISA_count+=a;
	p->current_students.FISA_development+=a;
	p->current_students.FISA_durability+=a;
}



int new_staff_available(struct board b){
	if ((b.n_turn)%5==0)
		return 1;
	else
		return 0;
	
}
/**
 * @brief computes number of student cards received by the player
 * @return number of student cards to be received
 */
int nb_student_card_received(struct ensiie ensiie){
	


}


/**
 * @brief ends current turn, computes and updates Sustainable Development (SD) points for each player
 * 
 */
void end_turn(struct board* board) {
	int development_player1, durability_player1, development_player2, durability_player2;
	
	development_player1 = (board->player1.current_students.FISE_count * board->player1.current_students.FISE_development) + (is_even(*board)) ? (board->player1.current_students.FISA_count * board->player1.current_students.FISA_development) : 0;

	development_player2 = (board->player2.current_students.FISE_count * board->player2.current_students.FISE_development) + (is_even(*board)) ? (board->player2.current_students.FISA_count * board->player2.current_students.FISA_development) : 0;

	durability_player1 = (board->player1.current_students.FISE_count * board->player1.current_students.FISE_durability) + (is_even(*board)) ? (board->player1.current_students.FISA_count * board->player1.current_students.FISA_durability) : 0;

	durability_player2 = (board->player2.current_students.FISE_count * board->player2.current_students.FISE_durability) + (is_even(*board)) ? (board->player2.current_students.FISA_count * board->player2.current_students.FISA_durability) : 0;

	board->player1.SD += max(development_player1 - durability_player2 + board->player1.SD_added - board->player1.SD_removed, 0);

	board->player2.SD += max(development_player2 - durability_player1 + board->player2.SD_added - board->player1.SD_removed);

}





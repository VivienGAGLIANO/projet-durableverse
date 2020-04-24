#include "../headers/interface.h"
#include "../headers/board.h"



struct board new_board(){
	struct board board;
	return board;
}

void free_board(struct board* b){
	free(b);
}

void begin_turn (struct board* b){
	b->n_turn+=1;
	if (is_peer(*b)) {
		b->player1.current_students.FISA_count=0;
		b->player2.current_students.FISA_count=0;
		b->player1.current_students.FISA_durability=0;
		b->player2.current_students.FISA_durability=0;
		b->player1.current_students.FISA_development=0;
		b->player2.current_students.FISA_development=0;
	}
	if ((b->n_turn-1)%5==0){
		b->player1.current_staff.max+=1;
		b->player2.current_staff.max+=1;
	}
}

void play_phase(struct ensiie* p, int a){

	int *nb_FISE;
	int *nb_FISA;
	choice_FISE_FISA(nb_FISE, nb_FISA, *p);
	

}

int nb_card_drawn(struct ensiie p){


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

void draw(struct ensiie* p){
	



}

int new_staff_available(struct board b){
	if ((b.n_turn)%5==0)
		return 1;
	else
		return 0;
	
}

int nb_student_card_received(struct ensiie player){

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





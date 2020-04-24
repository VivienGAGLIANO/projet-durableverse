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

	*nb_FISE;
	*nb_FISA;
	choice_FISE_FISA(nb_FISE, nb_FISA, p);
	

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
	p->



}

int new_staff_available(struct board b){
	if (b.n_turn)%5==0)
		return 1;
	else
		return 0;
	
}

void nb_student_card_received(stuct ensiie){

}



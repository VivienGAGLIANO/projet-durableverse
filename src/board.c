#include "../headers/interface.h"
#include "../headers/board.h"
#include "../headers/structure.h"


struct board new_board(){
	card_list all_cards= load_cards("../cards.xml");
	
	struct board board;

	struct ensiie player1;
	card_list deck1 = shuffle_stack(all_cards);
	card_list hand1 = create_stack();
	card_list discard1 = create_stack();
	struct board_staff current_staff1 = {
		.cards = create_stack(),
		.max = 1
	};
	struct board_student current_student1 = {
		.FISE_count = 0,
		.FISA_count = 0,
		.FISE_durability = 1,
		.FISA_durability = 1,
		.FISE_development = 1,
		.FISA_development = 1
	};
	
	struct ensiie player2;
	card_list deck2 = shuffle_stack(all_cards);
	card_list hand2 = create_stack();
	card_list discard2 = create_stack();
	struct board_staff current_staff2 = {
		.cards = create_stack(),
		.max = 1
	};
	struct board_students current_student2 = {
		.FISE_count = 0,
		.FISA_count = 0,
		.FISE_durability = 1,
		.FISA_durability = 1,
		.FISE_development = 1,
		.FISA_development = 1
	};
	
	player1 = {
		.SD = 0,
		.player_name = "Jaquie",
		.deck = deck1,
		.hand = hand1,
		.discard = discard1,
		.current_staff = current_staff1,
		.current_students = current_student1,
		.opponent = &player2,
		.SD_added = 0,
		.SD_removed = 0

	};

	player2 = {
		.SD = 0,
		.player_name = "Michel",
		.deck = deck2,
		.hand = hand2,
		.discard = discard2,
		.current_staff = current_staff2,
		.current_students = current_student2,
		.opponent = &player1,
		.SD_added = 0,
		.SD_removed = 0
	};


	board = (struct board) malloc(sizeof(board)); 
	board = {
		.player1 = player1,
		.player2 = player2,
		.n_turn = 0
	}

	for (int i = 0; i < 2; i++) {
		draw(&player1);
		draw(&player2);
	}
	return board;
}

void free_board(struct board* b){
	free_stack(&(b->player1.deck));
	free_stack(&(b->player1.hand));
	free_stack(&(b->player1.discard));
	free_stack(&(b->player1.current_staff.cards));
	free(&(b->player1.current_staff));
	free(b->player1);

	free_stack(&(b->player2.deck));
	free_stack(&(b->player2.hand));
	free_stack(&(b->player2.discard));
	free_stack(&(b->player2.current_staff.cards));
	free(&(b->player2.current_staff));
	free(b->player2);

	free(b);
}

void begin_turn (struct board* b){
	b->n_turn+=1;
	if (new_staff_available(*b)) {
		b->player1.current_staff.max++;
		b->player2.current_staff.max++;
	}

	print_new_turn(*b);
}

/* A revoir */
void play_phase(struct ensiie* p, int a){

	*nb_FISE;
	*nb_FISA;
	choice_FISE_FISA(nb_FISE, nb_FISA, p);
	

}

/* A revoir -> utiliser les effect list*/
int nb_card_drawn(struct ensiie p)
{
	int card_drawn = 1;

	while ()
	
	
	
	/*card_list a = copy_stack(p.current_staff.cards);
	card b;
	while (a!=NULL)
	{	
		b=pop_card(&a);
		if(b.name=="Massinissa Merabet")
			i+=2;
		else if (b.name=="Anne-Laure Ligozat" || b.name=="Catherine Dubois" || b.name=="Laurent Prével")
			i+=1;
	}
	return i;
	*/
}

void draw(struct ensiie* p) {
	push_card(pop_card (p->deck), p->hand);
}

/* A revoir -> utiliser les effect_list*/
int nb_student_card_received(struct ensiie p)
{
	int i = 0;
	card_list a = copy_stack(p.current_staff.cards);
	card b;
	while (a!=NULL)
	{	
		b=pop_card(&a);
		if(b.name=="Laurent Prével")
			i+=2;
		else if (b.name=="Anne-Laure Ligozat" || b.name=="Catherine Dubois" || b.name=="Katrin Salhab" || b.name=="Abass Sagna")
			i+=1;
		else
			i+=0;
	}
	return i;
}

void add_student_FISE(int nb, struct ensiie* p){
	p->current_students.FISE_count += nb;
}

void add_student_FISA(int nb, struct ensiie* p) {
	p->current_students.FISA_count += nb;
}

/* A revoir*/
int available_EP(struct ensiie p)
{
	return p.current_students.FISA_count*2+ p.current_students.FISE_count;
}

int play_card (struct ensiie *p, int *ep, card a){}

int is_over(struct board b){
	if ((b.n_turn == 30) || b.player1.SD > 20 || b.player2.SD > 20)
		return 1;
	else
		return 0;
}

int is_turn_even(struct board b) {
	return (b.n_turn)%2 == 0;
}

int new_staff_available(struct board b){
	return (b.n_turn - 1)%5 == 0;
}



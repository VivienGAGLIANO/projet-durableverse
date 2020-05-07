#include "../headers/interface.h"
#include "../headers/board.h"
#include "../headers/structure.h"


struct board new_board(){
	card_list all_cards= load_cards("../cards.xml");
	
	struct board *board;

	struct ensiie player1;
	card_list deck1 = shuffle_stack(all_cards);
	card_list hand1 = create_stack();
	card_list discard1 = create_stack();
	struct board_staff current_staff1 = {
		.cards = create_stack(),
		.max = 1,
		.staff_effect = create_stack()
	};
	struct board_students current_student1 = {
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
		.max = 1,
		.staff_effect = create_stack()
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


	board = (struct board*) malloc(sizeof(board)); 
	*board = {
		.player1 = player1,
		.player2 = player2,
		.n_turn = 0
	}

	for (int i = 0; i < 2; i++) {
		draw(&player1);
		draw(&player2);
	}
	return *board;
}

void free_board(struct board* b){
	free_stack(&(b->player1.deck));
	free_stack(&(b->player1.hand));
	free_stack(&(b->player1.discard));
	free_stack(&(b->player1.current_staff.cards));
	free(&(b->player1.current_staff));
	free(&(b->player1));

	free_stack(&(b->player2.deck));
	free_stack(&(b->player2.hand));
	free_stack(&(b->player2.discard));
	free_stack(&(b->player2.current_staff.cards));
	free(&(b->player2.current_staff));
	free(&(b->player2));

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

void play_phase(struct board board, struct ensiie* p){
	print_new_phase(board, *p);
	
	//Adding student cards
	int *nb_FISE, *nb_FISA;
	choice_FISE_FISA(nb_FISE, nb_FISA, *p);
	add_student_FISE(*nb_FISE, p);
	add_student_FISA(*nb_FISA, p);

	//Playing cards
	struct card *chosen_card;
	while ((chosen_card = choice_card(*p)) != NULL)
		play_card(p, available_EP(board, *p), *chosen_card);
}

int nb_card_drawn(struct ensiie p)
{
	int card_drawn = 1;
	effect_list current_effect = p.current_staff.staff_effect;
	while (current_effect != NULL) {
		if (current_effect->head->id == DR)
			card_drawn += current_effect->head->value;
		current_effect = current_effect->tail;
	}
	return card_drawn;
}

void draw(struct ensiie* p) {
	push_card(pop_card (p->deck), p->hand);
}

int nb_student_card_received(struct ensiie p)
{
	int student_card_drawn = 1;
	effect_list current_effect = p.current_staff.staff_effect;
	while (current_effect != NULL) {
		if (current_effect->head->id == E)
			student_card_drawn += current_effect->head->value;
		current_effect =  current_effect->tail;
	}
	return student_card_drawn;
}

void add_student_FISE(int nb, struct ensiie* p){
	p->current_students.FISE_count += nb;
}

void add_student_FISA(int nb, struct ensiie* p) {
	p->current_students.FISA_count += nb;
}

int available_EP(struct board board, struct ensiie p)
{
	return is_turn_even(board) * 2 * p.current_students.FISA_count + p.current_students.FISE_count;
}

// /!\ Function implemented WITHOUT staff_effect list !!
int play_card (struct ensiie *p, int *ep, card a) {
	// a is an action card
	if (a.action_effect != NULL) {
		switch (a.action_effect)
		{
			case WinOneSD :
				p->SD++;
				break;

			case DrawOneCard :
				draw(p);
				break;

			case PlayOneFISE :
				p->current_students.FISE_count++;
				break;

			case PlayOneFISA :
				p->current_students.FISA_count++;
				break;

			case Win6EP :
				*ep += 6;
				break;

			case RemoveOneFISEFISA :
				p->opponent->current_students.FISE_count = max(p->opponent->current_students.FISE_count - 1, 0);
				p->opponent->current_students.FISA_count = max(p->opponent->current_students.FISA_count - 1, 0);
				break;

			case DiscardOneStaff :

				break;

			case ShuffleDiscardDraw :
				while (!is_stack_empty(p->discard))
					push(pop(&(p->discard)), &(p->deck));
				shuffle_stack(&(p->deck));
				break;

			case IncreaseDevelopment :
				p->current_students.FISE_development++;
				p->current_students.FISA_development++;
				break;

			case IncreaseDurability :
				p->current_students.FISE_durability++;
				p->current_students.FISA_durability++;
				break;

			case RemoveAllFISEFISA :
				p->current_students.FISE_count = 0;
				p->current_students.FISA_count = 0;
				p->opponent->current_students.FISE_count = 0;
				p->opponent->current_students.FISA_count = 0;
				break;

			default :
				printf("Error : action card with no effect %s\nAction cancelled\n", a.name);
				return 0;
		}
		*ep -= a.cost;
		remove_card(&(p->hand), seek_stack_elem(&a, p->hand));
		push_card(a, &(p->discard));
		return 1;
	}

	// a is a staff card
	if (!is_stack_empty(a.staff_effect)) {
		// staff_card threshold not reached
		if (stack_len(p->current_staff.cards) < p->current_staff.max) {
			push_card(a, &(p->current_staff.cards));
		}

		// staff_card threshold reached
		if (stack_len(p->current_staff.cards) >= p->current_staff.max) {
			card discarded_staff;
			push_card(discarded_staff = pop_last_card(&(p->current_staff.cards)), &(p->current_staff.cards));
			push_card(discarded_staff, &(p->discard));
		}

		*ep -= a.cost;
		remove_card(&(p->hand), seek_stack_elem(&a, p->hand));
		return 1;
	}

	else {
		printf("Error : non staff non action card %s\nAction cancelled\n", a.name);
		return 0;
	}
}

void end_turn(struct board *board) {
	//SD points gained by student card
	board->player1.SD += board->player1.current_students.FISE_count * board->player1.current_students.FISE_development - board->player2.current_students.FISE_count * board->player2.current_students.FISE_durability + is_turn_even(*board) * (board->player1.current_students.FISA_count * board->player1.current_students.FISA_development - board->player2.current_students.FISA_count * board->player2.current_students.FISA_durability);
	board->player2.SD += board->player2.current_students.FISE_count * board->player2.current_students.FISE_development - board->player1.current_students.FISE_count * board->player1.current_students.FISE_durability + is_turn_even(*board) * (board->player2.current_students.FISA_count * board->player2.current_students.FISA_development - board->player1.current_students.FISA_count * board->player1.current_students.FISA_durability);
	effect_list current_effect1 = board->player1.current_staff.staff_effect;
	effect_list current_effect2 = board->player2.current_staff.staff_effect;

	//SD points gained by staff card
	while (current_effect1 != NULL) {
		if (current_effect1->head->id == ADD)
			board->player1.SD += current_effect1->head->value;
		if (current_effect1->head->id == RDD)
			board->player2.SD -= current_effect1->head->value;
	}
		while (current_effect2 != NULL) {
		if (current_effect2->head->id == ADD)
			board->player2.SD += current_effect2->head->value;
		if (current_effect2->head->id == RDD)
			board->player1.SD -= current_effect2->head->value;
	}

	//Setting SD point to 0 if they are negative
	if (board->player1.SD < 0)
		board->player1.SD =0;
	if (board->player2.SD < 0)
		board->player2.SD = 0;
}

int is_over(struct board b){
	return b.n_turn == 30 || ((b.player1.SD > 20 || b.player2.SD > 20) * (b.player1.SD != b.player2.SD));
}

int is_turn_even(struct board b) {
	return (b.n_turn)%2 == 0;
}

int new_staff_available(struct board b){
	return (b.n_turn - 1)%5 == 0;
}



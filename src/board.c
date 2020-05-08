#include "../headers/interface.h"
#include "../headers/board.h"
#include "../headers/structure.h"


struct board new_board(char* name1, char* name2) {
	card_list all_cards = load_cards("../cards.xml");

	/* Creating player 1 */
	struct ensiie player1 = {
		.SD = 0,
		.player_name = name1,
		.deck = shuffle_stack(all_cards),
		.hand = create_stack(),
		.discard = create_stack(),
		.current_staff = {
			.cards = create_stack(),
			.max = 1
		},
		.current_students = {
			.FISE_count = 0,
			.FISA_count = 0,
			.FISE_durability = 1,
			.FISA_durability = 1,
			.FISE_development = 1,
			.FISA_development = 1
		}
	};

	/* Creating player 2 */
	struct ensiie player2 = {
		.SD = 0,
		.player_name = name2,
		.deck = shuffle_stack(all_cards),
		.hand = create_stack(),
		.discard = create_stack(),
		.current_staff = {
			.cards = create_stack(),
			.max = 1
		},
		.current_students = {
			.FISE_count = 0,
			.FISA_count = 0,
			.FISE_durability = 1,
			.FISA_durability = 1,
			.FISE_development = 1,
			.FISA_development = 1
		}
	};

	/* This will probably don't work because the
	 * struct ensiie is copied when allocated to the board
	 */
	player1.opponent = &player2;
	player2.opponent = &player1;

	/* Creating the board */
	struct board board = {
		.player1 = player1,
		.player2 = player2,
		.n_turn = 0
	};

	/* Same thing apply here: try this in case of failure: draw(&board.player1) */
	for (int i = 0; i < 2; i++) {
		draw(&player1);
		draw(&player2);
	}
	return board;
}

void free_board(struct board* b) {
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

void begin_turn(struct board* b) {
	b->n_turn+=1;
	if (new_staff_available(*b)) {
		b->player1.current_staff.max++;
		b->player2.current_staff.max++;
	}

	print_new_turn(*b);
}

void play_phase(struct board board, struct ensiie* p) {
	// Drawing cards
	for (int i = 0; i < nb_card_drawn(*p); i++)
		draw(p);
	
	print_new_phase(board, *p);

	// Adding student cards
	int *nb_FISE = NULL;
	int *nb_FISA = NULL;
	choice_FISE_FISA(nb_FISE, nb_FISA, *p);
	add_student_FISE(*nb_FISE, p);
	add_student_FISA(*nb_FISA, p);

	// Playing cards
	struct card *chosen_card;
	int ep = available_EP(board, *p);
	while ((chosen_card = choice_card(board, *p, chosen_card)) != NULL)
		play_card(p, &ep, *chosen_card);
}

int nb_card_drawn(struct ensiie p)
{
	int card_drawn = 1;
	effect_list current_effect = get_all_staff_effects(p.current_staff.cards);
	while (!is_stack_empty(current_effect)) {
		if (((staff_effect*) current_effect->head)->id == DR)
			card_drawn += ((staff_effect*) current_effect->head)->value;
		current_effect = current_effect->tail;
	}
	return card_drawn;
}

void draw(struct ensiie* p) {
	push_card(pop_card(&(p->deck)), &(p->hand));
}

int nb_student_card_received(struct ensiie p)
{
	int student_card_drawn = 1;
	effect_list current_effect = get_all_staff_effects(p.current_staff.cards);
	while (!is_stack_empty(current_effect)) {
		if (((staff_effect*) current_effect->head)->id == E)
			student_card_drawn += ((staff_effect*) current_effect->head)->value;
		current_effect =  current_effect->tail;
	}
	return student_card_drawn;
}

void add_student_FISE(int nb, struct ensiie* p) {
	p->current_students.FISE_count += nb;
}

void add_student_FISA(int nb, struct ensiie* p) {
	p->current_students.FISA_count += nb;
}

int available_EP(struct board board, struct ensiie p)
{
	return is_turn_even(board) * 2 * p.current_students.FISA_count + p.current_students.FISE_count;
}

int play_card (struct ensiie *p, int *ep, card a) {
	// a is an action card
	if (type_of_card(a) == ACTION_CARD) {
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
				p->opponent->current_students.FISE_count -= p->opponent->current_students.FISE_count - 1 < 0 ? 0 : 1;
				p->opponent->current_students.FISA_count -= p->opponent->current_students.FISA_count - 1 < 0 ? 0 : 1;
				break;

			case DiscardOneStaff :

				break;

			case ShuffleDiscardDraw :
				while (!is_stack_empty(p->discard))
					push(pop(&(p->discard)), &(p->deck));
				p->deck = shuffle_stack(p->deck);
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
				fprintf(stderr, "Error : action card with no effect %s\nAction cancelled\n", a.name);
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
		printf("Error: non staff non action card %s\nAction cancelled\n", a.name);
		return 0;
	}
}

int compute_development(struct board board, struct ensiie p) {
	// Basic development power (action card already counted)
	int development_FISE = p.current_students.FISE_development;
	int development_FISA = p.current_students.FISA_development;

	effect_list player_effect = get_all_staff_effects(p.current_staff.cards);
	effect_list opponent_effect = get_all_staff_effects(p.opponent->current_staff.cards);

	// Checking if player's staff affects those number
	while (!is_stack_empty(player_effect)) {
		if (((staff_effect*) player_effect->head)->id == AE1)
			development_FISE += ((staff_effect*) player_effect->head)->value;
		if (((staff_effect*) player_effect->head)->id == AA1)
			development_FISA += ((staff_effect*) player_effect->head)->value;
		player_effect = player_effect->tail;
	}

	// Checking if opponent's staff affects those number
	while (!is_stack_empty(opponent_effect)) {
		if (((staff_effect*) opponent_effect->head)->id == RE1) 
			development_FISE -= ((staff_effect*) opponent_effect->head)->value;
		if (((staff_effect*) opponent_effect->head)->id == RA1)
			development_FISA -= ((staff_effect*) opponent_effect->head)->value;
		opponent_effect = opponent_effect->tail;
	}

	// Resetting development power to 0 if negative
	development_FISE = development_FISE < 0 ? 0 : development_FISE;
	development_FISA = development_FISA < 0 ? 0 : development_FISA;

	// Returning actual development count, computed with student number (holding into account FISA disappearing)
	return p.current_students.FISE_count * development_FISE + is_turn_even(board) * p.current_students.FISA_count * development_FISA;

}

int compute_durability(struct board board, struct ensiie p) {
		// Basic development power (action card already counted)
	int durability_FISE = p.current_students.FISE_durability;
	int durability_FISA = p.current_students.FISA_durability;

	effect_list player_effect = get_all_staff_effects(p.current_staff.cards);
	effect_list opponent_effect = get_all_staff_effects(p.opponent->current_staff.cards);

	// Checking if player's staff affects those number
	while (!is_stack_empty(player_effect)) {
		if (((staff_effect*) player_effect->head)->id == AE2)
			durability_FISE += ((staff_effect*) player_effect->head)->value;
		if (((staff_effect*) player_effect->head)->id == AA2)
			durability_FISA += ((staff_effect*) player_effect->head)->value;
		player_effect = player_effect->tail;
	}

	// Checking if opponent's staff affects those number
	while (!is_stack_empty(opponent_effect)) {
		if (((staff_effect*) opponent_effect->head)->id == RE2) 
			durability_FISE -= ((staff_effect*) opponent_effect->head)->value;
		if (((staff_effect*) opponent_effect->head)->id == RA2)
			durability_FISA -= ((staff_effect*) opponent_effect->head)->value;
		opponent_effect = opponent_effect->tail;
	}

	// Resetting durability power to 0 if negative
	durability_FISE = durability_FISE < 0 ? 0 : durability_FISE;
	durability_FISA = durability_FISA < 0 ? 0 : durability_FISA;

	// Returning actual durability count, computed with student number (holding into account FISA disappearing)
	return p.current_students.FISE_count * durability_FISE + is_turn_even(board) * p.current_students.FISA_count * durability_FISA;
}

void end_turn(struct board *board) {
	// SD points gained by student card
	board->player1.SD += compute_development(*board, board->player1) - compute_durability(*board, board->player2);

	board->player2.SD += compute_development(*board, board->player2) - compute_durability(*board, board->player1);

	effect_list current_effect1 = get_all_staff_effects(board->player1.current_staff.cards);
	effect_list current_effect2 = get_all_staff_effects(board->player2.current_staff.cards);

	// SD points gained by staff card
	while (!is_stack_empty(current_effect1)) {
		if (((staff_effect*) current_effect1->head)->id == ADD)
			board->player1.SD += ((staff_effect*) current_effect1->head)->value;
		if (((staff_effect*) current_effect1->head)->id == RDD)
			board->player2.SD -= ((staff_effect*) current_effect1->head)->value;
	}
		while (!is_stack_empty(current_effect2)) {
		if (((staff_effect*) current_effect2->head)->id == ADD)
			board->player2.SD += ((staff_effect*) current_effect2->head)->value;
		if (((staff_effect*) current_effect2->head)->id == RDD)
			board->player1.SD -= ((staff_effect*) current_effect2->head)->value;
	}

	// Setting SD point to 0 if they are negative
	if (board->player1.SD < 0)
		board->player1.SD = 0;
	if (board->player2.SD < 0)
		board->player2.SD = 0;
}

int is_over(struct board b) {
	return b.n_turn == 30 || b.player1.SD > 20 || b.player2.SD > 20;
}

int is_turn_even(struct board b) {
	return (b.n_turn)%2 == 0;
}

int new_staff_available(struct board b) {
	return (b.n_turn - 1)%5 == 0;
}



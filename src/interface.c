#include <stdio.h>
#include "../headers/interface.h"



/**
 * @brief prints the hand
 * @details displays the given card list as a hand, in the format of a list with : card index in hand list, name of the card and energy cost.
 */
void print_hand(struct card* hand) {
    /* /!\ Card list type not defined yet. Come back later */    
}


/**
 * @brief prints new turn information 
 * @details prints turn number and each player's Sustainable Development (SD) points, states if new staff space is available and if FISA appear/disappear this turn
 * 
 */
void print_new_turn(struct board board) {
    system("clear");
    printf("------------ Starting turn %i ------------\n\n", board.n_turn);
    sleep(0.3);

    printf("Player %s : %i SD        vs        Player %s : %i SD\n\n", board.player1.player_name, board.player1.SD, board.player2.player_name, board.player2.SD);
    sleep(0.3);

    if (new_staff_available(board))
        printf("New staff emplacement available!\n");    
    
    if (is_turn_even(board)) 
        printf("/!\\ Turn is even : FISA now vanish from the board...\n");
    else 
        printf("/!\\ Turn is odd : FISA now appear on the board...\n");
    sleep(5);
}


/**
 * @brief prints new phase information
 * @details states which player's turn it is, prints the board (student cards, staff cards, and SD points of each player) as well as the current player's hand
 * 
 */
void print_new_phase(struct board board, struct ensiie current_player) {
    system("clear");
    printf("------------ Starting new phase ------------\n\n");
    sleep(0.3);

    printf("Player %s, it's your go!\n", current_player.player_name);
    sleep(0.3);

    print_board(board);
    printf("\n\n\n");

    print_hand(current_player.hand);
}


/**
 * @brief prints the current board
 * @details prints each player's SD points, student card number (FISE and FISA), staff card (by order played) and hand size
 */
void print_board(struct board board) {
    // Player 1 info
    printf("Player %s\n", board.player1.player_name);
    printf("SD : %i\n", board.player1.SD);
    printf("Card in hand : %i\n", len_stack(board.player1.hand));
    
    printf("\n");

    printf("Student cards : \n");
    printf("FISE : %i\n", board.player1.current_students.FISE_count);
    printf("FISA : %i\n", board.player1.current_students.FISA_count);

    printf("\n");

    printf("Staff cards : \n");
    for (int i = 0; i < stack_len(board.player1.current_staff.cards); i++)
        printf("%s\n");


    printf("\n\nVS\n\n");

    // Player 2 info
    printf("Player %s\n", board.player2.player_name);
    printf("SD : %i\n", board.player2.SD);
    printf("Card in hand : %i\n", len_stack(board.player2.hand));
    
    printf("\n");

    printf("Student cards : \n");
    printf("FISE : %i\n", board.player2.current_students.FISE_count);
    printf("FISA : %i\n", board.player2.current_students.FISA_count);

    printf("\n");

    printf("Staff cards : \n");
    for (int i = 0; i < stack_len(board.player2.current_staff.cards); i++)
        printf("%s\n");
}

void choice_FISE_FISA(int *nb_FISE, int *nb_FISA, struct ensiie p) {
    int student_cards_drawn = nb_student_card_received(p);
    printf("How many students cards do you want, %s ? You can receive %i cards this turn !\n", p.player_name, student_cards_drawn);

    int FISE_wanted;
    int FISA_wanted;
    fscanf("%i %i \n", &FISE_wanted, &FISA_wanted);

    if (FISE_wanted + FISA_wanted != student_cards_drawn) {
        while (FISE_wanted + FISE_wanted != student_cards_drawn) {
            printf("You have %i student card available, no more no less. Type in a correct combination !\n", student_cards_drawn);
            fscanf("%i %i \n", &FISE_wanted, &FISA_wanted);
        }
    }

    *nb_FISE = FISE_wanted;
    *nb_FISA = FISA_wanted;
}


/* Manque certaines fonctions */
/* TODO :
    choice_FISE_FISA
    choice_card
    print_end_game
*/


/**
 * @brief prints Durableverse logo and group name
 */
void print_logo() {
    printf(BOLDGREEN "%s", logo2);
    printf(BOLDYELLOW "%s\n\n" RESET, peaky);
}

/**
 * @brief clears console
 */
void clear_screen() {
    system("@cls||clear");
}

/**
 * @brief prints Durableverse logo and asks user for each player's name
 * @param name1 name of the first player
 * @param name2 name of the second player
 * @post name1 and name2 are updated with the names entered by each player
 */
void welcome_screen(char* name1, char* name2) {
    clear_screen();
    print_logo();
    printf("First player name: ");
    scanf("%s", name1);

    clear_screen();
    print_logo();
    printf("First player name: %s", name1);
    printf("                2nde player name: ");
    scanf("%s", name2);
}

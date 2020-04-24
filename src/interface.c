#include <stdio.h>

#include "../headers/interface.h"
#include "../headers/structure.h"
#include "../headers/board.h"



/**
 * @brief prints the hand
 * @detail displays the given card list as a hand, in the format of a list with : card index in hand list, name of the card and energy cost.
 */
void print_hand(struct card* hand) {
    /* /!\ Card list type not defined yet. Come back later */    
}


/**
 * @brief prints new turn information 
 * @detail prints turn number and each player's Sustainable Development (SD) points, states if new staff space is available and if FISA appear/disappear this turn
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
    
    if (is_even(board)) 
        printf("/!\\ Turn is even : FISA now vanish from the board...\n");
    else 
        printf("/!\\ Turn is odd : FISA now appear on the board...\n");
    sleep(5);
}


/**
 * @brief prints new phase information
 * @detail states which player's turn it is, prints the board (student cards, staff cards, and SD points of each player) as well as the current player's hand
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
 * @detail prints each player's SD points, student card number (FISE and FISA), staff card (by order played) and hand size
 */
void print_board(struct board board) {
    printf("Player %s\n", board.player1.player_name);
    printf("SD : %i\n", board.player1.SD);
    printf("Card in hand : %i\n", len_stack(board.player1.hand));
    
    printf("\n");

    printf("FISE : %i\n", board.player1.current_students.FISE_count);
    printf("FISA : %i\n", board.player1.current_students.FISA_count);

    /* A finir */
}
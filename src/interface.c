#include <stdio.h>
#include "../headers/interface.h"
#include "unistd.h" // sleep



/**
 * @brief prints the hand
 * @details displays the given card list as a hand, in the format of a list with : card index in hand list, name of the card and energy cost.
 * @param cards the card_list to print as a hand
 */
void print_hand(card_list cards) {
    for (int i = 0; i < stack_len(cards); i++) {
        card card = get_card(cards, i);
        printf("[card number:"PRINT_CARD_COLOR"%2i"RESET"; name: "PRINT_CARD_COLOR"%s"RESET"; cost: "PRINT_CARD_COLOR"%i"RESET"]\n", i+1, card.name, card.cost);
    }
}

/**
 * @brief prints new turn information 
 * @details prints turn number and each player's Sustainable Development (SD) points, states if new staff space is available and if FISA appear/disappear this turn
 * @param board the game board
 */
void print_new_turn(struct board board) {
    clear_screen();
    printf("------------ Starting turn %i ------------\n\n", board.n_turn);
    sleep(0.3);

    printf(PLAYER1_COLOR "Player %s : %i SD" RESET, board.player1.player_name, board.player1.SD);
    printf("        " INVERTED "vs" RESET "        ");
    printf(PLAYER2_COLOR "Player %s : %i SD\n\n" RESET, board.player2.player_name, board.player2.SD);
    sleep(0.3);

    if (new_staff_available(board))
        printf("New staff emplacement available!\n");    
    
    if (is_turn_even(board)) 
        printf("/!\\ Turn is even : FISA now vanish from the board...\n");
    else 
        printf("/!\\ Turn is odd : FISA now appear on the board...\n");
    sleep(3);
}


/**
 * @brief prints new phase information
 * @details states which player's turn it is, prints the board (student cards, staff cards, and SD points of each player) as well as the current player's hand
 * @param board the game board
 * @param current_player the player which is currently playing
 */
void print_new_phase(struct board board, struct ensiie current_player) {
    system("clear");
    printf("----------------- Turn %2d ------------------\n", board.n_turn);
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
 * @param board the current board
 */
void print_board(struct board board) {
    clear_screen();
    
    // Player 1 info
    printf(PLAYER1_COLOR "Player %s\n", board.player1.player_name);
    printf("SD : %i\n", board.player1.SD);
    printf("Card in hand : %i\n", stack_len(board.player1.hand));
    
    printf("\n");

    printf("Student cards : \n");
    printf("FISE : %i\n", board.player1.current_students.FISE_count);
    printf("FISA : %i\n", board.player1.current_students.FISA_count);

    printf("\n");

    printf("Staff cards : \n");
    for (int i = 0; i < stack_len(board.player1.current_staff.cards); i++)
        printf("    %s\n", ((card*) board.player1.current_staff.cards->head)->name);

    printf(RESET INVERTED "\n\nVS\n\n\n" RESET);

    // Player 2 info
    printf(PLAYER2_COLOR "Player %s\n", board.player2.player_name);
    printf("SD : %i\n", board.player2.SD);
    printf("Card in hand : %i\n", stack_len(board.player2.hand));
    
    printf("\n");

    printf("Student cards : \n");
    printf("FISE : %i\n", board.player2.current_students.FISE_count);
    printf("FISA : %i\n", board.player2.current_students.FISA_count);

    printf("\n");

    printf("Staff cards : \n");
    for (int i = 0; i < stack_len(board.player2.current_staff.cards); i++)
        printf("    %s\n", ((card*) board.player2.current_staff.cards->head)->name);

    printf("\n\n\n");
    
    printf(RESET);
}

/**
 * @brief asks player which student cards he desires
 * @details asks which student cards (FISE or FISA) are wanted, in accordance with the number of student card available for this player (computed using nb_student_card_received function)
 * If only one available, asks between FISE and FISA
 * Else asks how many of each, and verifies that the sum equals number of student cards available
 * Result is stored in given nb_FISE and nb_FISA variables
 * @param nb_FISE a pointer to an int in which will be stored the number of FISE the player wants
 * @param nb_FISA a pointer to an int in which will be stored the number of FISA the player wants
 * @param p the player which is currently playing
 * @pre nb_FISE and nb_FISA have to be allocated
 * @post *nb_FISE and *nb_FISA are updated
 */
void choice_FISE_FISA(int *nb_FISE, int *nb_FISA, struct ensiie p) {
    int student_cards_drawn = nb_student_card_received(p);
    printf("How many students cards do you want, %s ? You can receive %i card%s this turn !\n", p.player_name, student_cards_drawn, student_cards_drawn > 1 ? "s":"");

    int FISE_wanted = 0;
    int FISA_wanted = 0;
    printf("FISE cards desired ? ");
    scanf("%i", &FISE_wanted);

    printf("FISA cards desired ? ");
    scanf("%i", &FISA_wanted);

    while (FISE_wanted + FISA_wanted != student_cards_drawn || FISE_wanted < 0 || FISA_wanted < 0 ) {
        if (FISE_wanted + FISA_wanted != student_cards_drawn) 
            printf("You have %i student card available, no more no less. ", student_cards_drawn);
        if (FISE_wanted < 0 || FISA_wanted < 0)
            printf("Cannot pick negative student cards number. ");
        printf("Type in a correct combination !\n");

        printf("FISE cards desired ? ");
        scanf("%i", &FISE_wanted);

        printf("FISA cards desired ? ");
        scanf("%i", &FISA_wanted);
    }

    *nb_FISE = FISE_wanted;
    *nb_FISA = FISA_wanted;
}

/**
 * @brief asks the player to play a card or end his phase
 * @details Checks if chosen card's cost doesn't exceed available Energy Point (EP), and asks again with error message if it does. Returns the index of the card chosen in the hand of the player.
 * @param board the game board
 * @param p the ensiie which is currently playing
 * @param EP the current available EP of the player
 * @return the index of the card chosen in player's hand, or -1 if the player wants to end his turn
 */
int choice_card(struct board board, struct ensiie p, int EP) {
    print_hand(p.hand);

    printf("You have %i Energy Point available, what card would you like to play? (type 0 if you wish to pass turn)\n", EP);
    int chosen_card_index;

    scanf("%i", &chosen_card_index);

    if (chosen_card_index == 0) 
        return -1;
    if (chosen_card_index > stack_len(p.hand) || chosen_card_index < 0) {
        printf("Card chosen is outside hand's range. Pick again !\n");
        return choice_card(board, p, EP);
    }
    if (get_card(p.hand, chosen_card_index - 1).cost > EP) {
        printf("You don't have enough Energy Points for that ! Pick again ! \n");
        return choice_card(board, p, EP);
    }
    return chosen_card_index - 1;
}

/**
 * @brief prints the winner or draw, depending on the result of the game
 * @param board the game board
 * @pre game must be over for the function to run, i.e. function is_over must return true
 */
void print_end_game(struct board board) {
    clear_screen();

    printf("Game finished !\n");

    if (board.player1.SD == board.player2.SD)
        printf("It's a draw !\n");

    else 
        printf("%s is the winner ! Congratulations\n", board.player1.SD > board.player2.SD ? board.player1.player_name : board.player2.player_name);
}

/**
 * @brief prints Durableverse logo and group name
 */
void print_logo() {
    printf(LOGO_COLOR      "%s"      RESET, LOGO);
    printf(GROUPNAME_COLOR "%s\n\n"  RESET, PEAKY_BLINDERS);
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
    scanf("%[^\n]%*c", name1);

    clear_screen();
    print_logo();
    printf("First player name: %s", name1);
    printf("                Second player name: ");
    scanf("%[^\n]%*c", name2);
}

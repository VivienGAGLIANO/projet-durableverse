#include <stdio.h>
#include <unistd.h> // sleep
#include <math.h> // log10 for display_card
#include <string.h> // strlen for display_card
#include <sys/ioctl.h> //ioctl for getting terminal size
#include <unistd.h> // STDOUT_FILENO for getting terminal size
#include <stdlib.h> // malloc for split_string

#include "../headers/interface.h"


/**
 * @brief prints the hand
 * @details displays the given card list as a hand, in the format of a list with : card index in hand list, name of the card and energy cost.
 * @param cards the card_list to print as a hand
 * @param highlight_card the index of the card to highlight, -1 for highlighting no card
 */
void print_hand(card_list cards, int highlight_card) {
    for (int i = 0; i < stack_len(cards); i++) {
        card card = get_card(cards, i);
        if (i == highlight_card)
            printf(INVERTED "[card number:%2i; name: %s; cost: %i]\n" RESET, i+1, card.name, card.cost);
        else
            printf("[card number:"PRINT_CARD_COLOR"%2i"RESET"; name: "PRINT_CARD_COLOR"%s"RESET"; cost: "PRINT_CARD_COLOR"%i"RESET"]\n", i+1, card.name, card.cost);
    }
    printf("\n");
}

/**
 * @brief prints new turn information 
 * @details prints turn number and each player's Sustainable Development (SD) points, states if new staff space is available and if FISA appear/disappear this turn
 * @param board the game board
 */
void print_new_turn(struct board board) {
    clear_screen();

    // Getting terminal size
    struct winsize termsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &termsize);

    int offset = 16 + log10(board.n_turn) + 1;
    for (int i = 0; i < (termsize.ws_col - offset) / 2; i++)
        printf("-");
    printf(" Starting turn %i ", board.n_turn);
    for (int i = 0; i < termsize.ws_col - (termsize.ws_col - offset) / 2 - offset; i++)
        printf("-");
    printf("\n\n");
    sleep(0.3);

    int size1 = 7 + strlen(board.player1.player_name) + 6 + log10(board.player1.SD ? board.player1.SD : 1) + 1;
    int size2 = 7 + strlen(board.player2.player_name) + 6 + log10(board.player2.SD ? board.player2.SD : 1) + 1;

    printf(PLAYER1_COLOR "Player %s : %i SD" RESET, board.player1.player_name, board.player1.SD);
    
    for (int i = 0; i < termsize.ws_col / 2 - size1 - 1; i++)
        printf(" ");
    printf(INVERTED "VS" RESET);
    for (int i = 0; i < termsize.ws_col - (termsize.ws_col / 2 - 1) - 2 - size2; i++)
        printf(" ");
    printf(PLAYER2_COLOR "Player %s : %i SD\n\n" RESET, board.player2.player_name, board.player2.SD);
    sleep(0.3);

    if (new_staff_available(board))
        printf("New staff emplacement available!\n");    
    
    if (is_turn_even(board)) 
        printf(BOLDRED "/!\\" RESET " Turn is even : FISA now " BOLDRED "vanish" RESET " from the board...\n");
    else 
        printf(BOLDRED "/!\\" RESET " Turn is odd : FISA now " BOLDRED "appear" RESET " on the board...\n");
    
    printf("\n" BOLDWHITE "[Type in anything to proceed]" RESET "\n");

    getchar();
}


/**
 * @brief prints new phase information
 * @details states which player's turn it is, prints the board (student cards, staff cards, and SD points of each player) as well as the current player's hand
 * @param board the game board
 * @param current_player the player which is currently playing
 */
void print_new_phase(struct board board, struct ensiie current_player) {
    clear_screen();

    // Getting terminal size
    struct winsize termsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &termsize);

    int offset = 7 + log10(board.n_turn ? board.n_turn : 1) + 1; // 7 corresponds to the number of char in _Turn__
    for (int i = 0; i < (termsize.ws_col - offset) / 2; i++)
        printf("-");
    printf(" Turn %d ", board.n_turn);
    for (int i = 0; i < termsize.ws_col - (termsize.ws_col - offset) / 2 - offset; i++)
        printf("-");
    printf("\n");
    
    offset = 20; // 2O corresponds to the number of char in _Starting_new_phase_
    for (int i = 0; i < (termsize.ws_col - offset) / 2; i++)
        printf("-");
    printf(" Starting new phase ");
    for (int i = 0; i < termsize.ws_col - (termsize.ws_col - offset) / 2 - offset; i++)
        printf("-");
    printf("\n\n");
    sleep(0.5);

    printf("Player " BOLDCYAN "%s" RESET ", it's your go!\n", current_player.player_name);

    printf("\n" BOLDWHITE "[Type in anything to proceed]" RESET "\n");
    getchar();

    print_board(board);

    print_hand(current_player.hand, -1);
}


/**
 * @brief prints the current board
 * @details prints each player's SD points, student card number (FISE and FISA), staff card (by order played) and hand size
 * @param board the current board
 */
void print_board(struct board board) {
    clear_screen();
    
    // Getting terminal size
    struct winsize termsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &termsize);

    for (int i = 0; i < termsize.ws_col / 2; i++)
        printf(" ");
    printf(RESET INVERTED "VS" RESET);
    for (int i = 0; i < termsize.ws_col / 2; i++)
        printf(" ");
    printf("\n");

    // Player names
    int name_size1 = 7 + strlen(board.player1.player_name); // 7 corresponds to number of char in Player_
    int name_size2 = 7 + strlen(board.player2.player_name);

    printf(PLAYER1_COLOR "Player %s", board.player1.player_name);
    for (int i = 0; i < termsize.ws_col - name_size1 - name_size2; i++)
        printf(" ");
    printf(PLAYER2_COLOR "Player %s\n", board.player2.player_name);
    

    // SD points
    int SD_size1 = 5 + log10(board.player1.SD ? board.player1.SD : 1) + 1; // 5 corresponds to number of char in SD_:_
    int SD_size2 = 5 + log10(board.player2.SD ? board.player2.SD : 1) + 1;

    printf(PLAYER1_COLOR "SD : %i", board.player1.SD);
    for (int i = 0; i < termsize.ws_col - SD_size1 - SD_size2; i++)
        printf(" ");
    printf(PLAYER2_COLOR "SD : %i\n", board.player2.SD);

    // Card in hand
    int hand_size1 = 16 + log10(stack_len(board.player1.hand) ? stack_len(board.player1.hand) : 1) + 1; // 15 corresponds to number of char in Cards in hand_:_
    int hand_size2 = 16 + log10(stack_len(board.player2.hand) ? stack_len(board.player2.hand) : 1) + 1;

    printf(PLAYER1_COLOR "Cards in hand : %i", stack_len(board.player1.hand));
    for (int i = 0; i < termsize.ws_col - hand_size1 - hand_size2; i++)
        printf(" ");
    printf(PLAYER2_COLOR "Cards in hand : %i\n", stack_len(board.player2.hand));

    printf("\n");

    // Student cards
    printf(PLAYER1_COLOR "Student cards :");
    for (int i = 0; i < termsize.ws_col - 2*15; i++) // 14 corresponds to the number of char in Student cards_:
        printf(" ");
    printf(PLAYER2_COLOR "Student cards :\n");
    
    // FISE
    int FISE_size1 = 11 + log10(board.player1.current_students.FISE_count ? board.player1.current_students.FISE_count : 1) + 1; // 11 corresponds to number of char in ____FISE_:_
    int FISE_size2 = 11 + log10(board.player2.current_students.FISE_count ? board.player2.current_students.FISE_count : 1) + 1;

    printf(PLAYER1_COLOR "    FISE : %i", board.player1.current_students.FISE_count);
    for (int i = 0; i < termsize.ws_col - FISE_size1 - FISE_size2; i++)
        printf(" ");
    printf(PLAYER2_COLOR "FISE : %i    \n", board.player2.current_students.FISE_count);

    // FISA
    int FISA_size1 = 11 + log10(board.player1.current_students.FISA_count ? board.player1.current_students.FISA_count : 1) + 1; // 11 corresponds to number of char in ____FISA_:_
    int FISA_size2 = 11 + log10(board.player2.current_students.FISA_count ? board.player2.current_students.FISA_count : 1) + 1;

    printf(PLAYER1_COLOR "    FISA : %i", board.player1.current_students.FISA_count);
    for (int i = 0; i < termsize.ws_col - FISA_size1 - FISA_size2; i++)
        printf(" ");
    printf(PLAYER2_COLOR "FISA : %i    \n", board.player2.current_students.FISA_count);

    printf("\n");

    // Staff cards
    printf(PLAYER1_COLOR "Staff cards :");
    for (int i = 0; i < termsize.ws_col - 2*13; i++) // 13 corresponds to the number of char in Staff cards_:
        printf(" ");
    printf(PLAYER2_COLOR "Staff cards :\n");

    //Staff lists #le génie intervient
    int nb_staff1 = stack_len(board.player1.current_staff.cards);
    int nb_staff2 = stack_len(board.player2.current_staff.cards);

    for (int nb_staff = 0; nb_staff < (nb_staff1 < nb_staff2 ? nb_staff2 : nb_staff1); nb_staff++) {
        int staff_size1 = nb_staff < nb_staff1 ? strlen(get_card(board.player1.current_staff.cards, nb_staff).name) + 4 : 0; // 4 corresponds to the offset to margin before staff card name
        int staff_size2 = nb_staff < nb_staff2 ? strlen(get_card(board.player2.current_staff.cards, nb_staff).name) + 4 : 0;

        if (nb_staff < nb_staff1)
            printf(PLAYER1_COLOR "    %s" RESET, get_card(board.player1.current_staff.cards, nb_staff).name);
        for (int i = 0; i < termsize.ws_col - staff_size1 - staff_size2; i++)
            printf(" ");
        if (nb_staff < nb_staff2)
            printf(PLAYER2_COLOR "%s    \n" RESET, get_card(board.player2.current_staff.cards, nb_staff).name);
    }

    printf(RESET "\n\n\n");
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
 * @brief splits the given string in several pieces of size size
 * @param string the string to split
 * @param size the size of each chunk (except the last one which may be smaller)
 * @return a char** in which the chunks are stored
 */
char** split_string(char* string, int size) {
    int n = (strlen(string) / size) + 1;
    char** chunks = (char**) malloc(n*sizeof(char*));
    for (int i = 0; i < n; i++) {
        chunks[i] = (char*) malloc((size+1)*sizeof(char));
        strncpy(chunks[i], string + i*size, size);
        chunks[i][size] = '\0';
    }
    return chunks;
}

/**
 * @brief display the given card in terminal ascii art
 * @details the card will be printed at center of the terminal with its name, cost, and effect in an ascii art card structure
 * @param card the card to display
 * @param width the width the card should take
 */
void display_card(card card, int width) {
    // Getting terminal size
    struct winsize termsize;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &termsize);
    
    for (int i = 0; i < (termsize.ws_col - width) / 2; i++)
        printf(" ");
    printf(" ");
    for (int i =0; i < width; i++)
        printf("_");
    printf(" \n"); 
    
    // Name & Cost
    for (int i = 0; i < (termsize.ws_col - width) / 2; i++)
        printf(" ");
    printf("|");
    printf("%s", card.name);
    for (int i = 0; i < width - (int) strlen(card.name) - ((int) log(card.cost)); i++)
        printf(" ");
    printf("%i", card.cost);
    printf("|\n");

    for (int i = 0; i < (termsize.ws_col - width) / 2; i++)
        printf(" ");
    printf("|");
    for (int i = 0; i < width; i++)
        printf("_");
    printf("|\n");

    // Type
    char* type = card.type == ACTION_CARD ? "Action" : "Personnel";
    for (int i = 0; i < (termsize.ws_col - width) / 2; i++)
        printf(" ");
    printf("|");
    for (int i = 0; i < width - (int) strlen(type); i++)
        printf(" ");
    printf("%s", type);
    printf("|\n");

    for (int i = 0; i < (termsize.ws_col - width) / 2; i++)
        printf(" ");
    printf("|");
    for (int i = 0; i < width; i++)
        printf("_");
    printf("|\n");

    // Effect : action card
    if (card.type == ACTION_CARD) {
        char** split_description = split_string(card.desc, width);
        for (int j = 0; j < strlen(card.desc) / width + 1; j++) {
            for (int i = 0; i < (termsize.ws_col - width) / 2; i++)
                printf(" ");
            printf("|");
            printf("%s", split_description[j]);
            for (int i = 0; i < width - (int) strlen(split_description[j]); i++)
                printf(" ");
            printf("|\n");
        }
    }

    // Effect : staff card
    if (card.type == STAFF_CARD) {
        for (int nb_eff = 0; nb_eff < stack_len(card.staff_effect); nb_eff++) {
            char* description = get_effect(card.staff_effect, nb_eff).desc;
            char** split_description = split_string(description, width);

            for (int j = 0; j < strlen(description) / width + 1; j++) {
                for (int i = 0; i < (termsize.ws_col - width) / 2; i++)
                    printf(" ");
                printf("|");
                printf("%s", split_description[j]);
                for (int i = 0; i < width - strlen(split_description[j]); i++)
                    printf(" ");
                printf("|");
            }
        }
    }

    for (int i = 0; i < (termsize.ws_col - width) / 2; i++)
        printf(" ");
    printf("|");
    for (int i =0; i < width; i++)
        printf("_");
    printf("|\n");

    printf("\n");
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
    print_hand(p.hand, -1);

    printf("You have %i Energy Point available, what card would you like to play, %s ? (type 0 if you wish to pass turn)\n", EP, p.player_name);
    int chosen_card_index = 0, previous_chosen_card;
    scanf("%i%*c", &chosen_card_index);

    while (chosen_card_index != 0) {
        if (chosen_card_index > stack_len(p.hand) || chosen_card_index < 0) {
            print_board(board);
            printf(BOLDRED "Card chosen is outside hand's range. Pick again !\n" RESET);
            return choice_card(board, p, EP);
        }

        print_board(board);
        print_hand(p.hand, chosen_card_index - 1);
        display_card(get_card(p.hand, chosen_card_index - 1), 50);
        printf("%i Energy Point available.\n", EP);

        printf("Card %d chosen ! Enter %d again to confirm, 0 to cancel and finish turn, or another card number to choose another card : ", chosen_card_index, chosen_card_index);
        previous_chosen_card = chosen_card_index;
        scanf("%i%*c", &chosen_card_index);
        if (previous_chosen_card == chosen_card_index) {
            if (get_card(p.hand, chosen_card_index - 1).cost > EP) {
                print_board(board);
                printf(BOLDRED "You don't have enough Energy Points for that ! Pick again ! \n" RESET);
                return choice_card(board, p, EP);
            } else
                return chosen_card_index - 1;
        }
    }
    return -1;
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

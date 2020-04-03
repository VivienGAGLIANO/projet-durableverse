#include <stdio.h>

#include "../headers/interface.h"
#include "../headers/structure.h"
#include "../headers/board.h"




void print_new_turn(struct board board) {
    system("clear");
    printf("------------ Starting turn %i ------------\n\n", board.n_turn);
    sleep(0.3);

    printf("Player 1 : %i SD        vs        Player 2 : %i SD\n\n", board.player1.SD, board.player2.SD);
    sleep(0.3);

    if (new_staff_available(board))
        printf("New staff emplacement available!\n");    
    
    if (is_even(board)) 
        printf("/!\\ Turn is even : FISA now vanish from the board...\n");
    else 
        printf("/!\\ Turn is odd : FISA now appear on the board...\n");
    sleep(0.3);
}

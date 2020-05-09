#include <stdlib.h>
#include <time.h>
#include "headers/board.h"
#include "headers/interface.h"

int main() {
    
    /* Initializing the game board */
    char name1[256], name2[256];
    welcome_screen(name1, name2);
    struct board *game_board = new_board(name1, name2);

    /* Choosing randomly the first player */
    srand(time(NULL));
    int playerOnePlaysFirst = rand() % 2;
    
    while (!is_over(*game_board)) {
        begin_turn(game_board);
        print_new_turn(*game_board);

        if (playerOnePlaysFirst) {
            play_phase(game_board, &game_board->player1);
            play_phase(game_board, &game_board->player2);
            playerOnePlaysFirst = 0;
        } else {
            play_phase(game_board, &game_board->player2);
            play_phase(game_board, &game_board->player1);
            playerOnePlaysFirst = 1;
        }
        end_turn(game_board);
    }

    print_end_game(*game_board);
    return 0;
}

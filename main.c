#include <stdlib.h>
#include <time.h>
#include "board.h"

int main(int argc, char const *argv[]) {
    
    /* Initializing the game board */
    struct board game_board = new_board();

    /* Choosing randomly the first player */
    srand(time(NULL));
    int playerOnePlaysFirst = rand() % 2;
    
    while (!is_over(game_board)) {
        begin_turn(&game_board);
        print_new_turn(game_board);

        if (playerOnePlaysFirst) {
            play_phase(&game_board.player1);
            play_phase(&game_board.player2);
            playerOnePlaysFirst = 0;
        } else {
            play_phase(&game_board.player2);
            play_phase(&game_board.player1);
            playerOnePlaysFirst = 1;
        }
        end_turn(&game_board);
    }

    print_end_game(game_board);
    return 0;
}

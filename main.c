#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "interface.h"

int main() {
    
    /* Initializing the game board */
    struct board game_board = new_board();

    /* Choosing randomly the first player */
    srand(time(NULL));
    int playerOnePlaysFirst = rand() % 2;
    
    while (!is_over(game_board)) {
        begin_turn(&game_board);
        print_new_turn(game_board);

        if (playerOnePlaysFirst) {
            play_phase(&game_board.player1, game_board.n_turn);
            play_phase(&game_board.player2, game_board.n_turn);
            playerOnePlaysFirst = 0;
        } else {
            play_phase(&game_board.player2, game_board.n_turn);
            play_phase(&game_board.player1, game_board.n_turn);
            playerOnePlaysFirst = 1;
        }
        end_turn(&game_board);
    }

    print_end_game(game_board);
    return 0;
}

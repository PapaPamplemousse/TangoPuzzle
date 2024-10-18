/** @file main.c
 *  @brief Entry point of the game.
 */

#include "../inc/ui.h"
#include "../inc/game_state.h"

int main() {
    GameState state;
    srand((unsigned int)time(NULL));

    /* Initialize ncurses */
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    /* Initialize colors */
    start_color();
    use_default_colors();
    init_pair(1, COLOR_RED, -1);   /* For error messages */
    init_pair(2, COLOR_GREEN, -1); /* For positive messages */

    /* Initialize game state */
    initialize_game_state(&state);

    /* Main game loop */
    while (1) {
        main_game_loop(&state);
    }

    /* End ncurses mode */
    endwin();
    return 0;
}

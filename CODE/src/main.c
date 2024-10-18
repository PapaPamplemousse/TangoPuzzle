/** @file main.c
 *  @brief Entry point of the game.
 */

#include "../inc/ui.h"
#include "../inc/game_state.h"
#include "../inc/timer.h"

int main() {
    GameState state;
    Timer timer;
    srand((unsigned int)time(NULL));

    /* Initialize ncurses */
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);

    /* Initialize colors */
    start_color();
    use_default_colors();
    init_pair(COLOR_ERROR, COLOR_RED, -1);      /* For error messages */
    init_pair(COLOR_SUCCESS, COLOR_GREEN, -1);  /* For positive messages */
    init_pair(COLOR_HIGHSCORE, COLOR_CYAN, -1); /* For high scores */

    /* Initialize game state */
    initialize_game_state(&state);

    /* Main game loop */
    while (1) {
        main_game_loop(&state, &timer);
    }

    /* End ncurses mode */
    endwin();
    return 0;
}

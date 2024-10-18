/** @file ui.c
 *  @brief Implementation of user interface functions.
 */
/** @file ui.c
 *  @brief Implementation of user interface functions.
 */

#include "../inc/ui.h"
#include "../inc/solver.h"
#include "../inc/game_state.h"
#include "../inc/timer.h"
#include "../inc/high_score.h"
#include "../inc/utils.h"
#include <string.h>

void main_game_loop(GameState *state, Timer *timer) {
    int cursor_x = 0, cursor_y = 0;
    int game_won = 0;
    char message[100] = "";
    char player_name[50] = "Player"; // Default player name
    double elapsed_time = 0.0;
    HighScoreEntry high_scores[MAX_HIGH_SCORES];
    int high_score_count = 0;

    // Load high scores
    load_high_scores(high_scores, &high_score_count);

    // Start the timer
    start_timer(timer);

    while (1) {
        clear();
        /* Draw the game grid */
        draw_game_grid(state, cursor_x, cursor_y);

        /* Display current elapsed time */
        elapsed_time = difftime(time(NULL), timer->start_time);
        mvprintw(0, 0, "Time: %.0f seconds", elapsed_time);

        /* Display high scores */
        int y_offset = GRID_SIZE * (CELL_HEIGHT + 1) + 1;
        display_high_scores(high_scores, high_score_count, y_offset);

        /* Check for rule violations */
        char violations[100][100];
        int violation_count = 0;
        check_rules(state, violations, &violation_count);

        int message_offset = y_offset + high_score_count + 2;

        if (violation_count > 0) {
            for (int idx = 0; idx < violation_count; idx++) {
                display_message(violations[idx], COLOR_ERROR, message_offset + idx);
            }
        } else {
            if (is_grid_filled(state->grid)) {
                // Stop the timer
                stop_timer(timer);
                elapsed_time = get_elapsed_time(timer);
                game_won = 1;
                snprintf(message, sizeof(message), "Congratulations, you have won in %.0f seconds!", elapsed_time);
                display_message(message, COLOR_SUCCESS, message_offset);

                // Get player's name
                echo();
                mvprintw(message_offset + 2, 0, "Enter your name: ");
                getnstr(player_name, sizeof(player_name) - 1);
                noecho();

                // Add to high scores
                HighScoreEntry new_score;
                strncpy(new_score.player_name, player_name, sizeof(new_score.player_name));
                new_score.time_seconds = elapsed_time;
                add_high_score(high_scores, &high_score_count, new_score);
                save_high_scores(high_scores, high_score_count);

                // Display updated high scores
                clear();
                draw_game_grid(state, cursor_x, cursor_y);
                display_high_scores(high_scores, high_score_count, y_offset);
                display_message("New High Score!", COLOR_SUCCESS, message_offset);
                refresh();

                // Wait for user input
                mvprintw(message_offset + 2, 0, "Press any key to continue...");
                getch();
                break;
            } else {
                display_message("The grid is valid so far.", COLOR_SUCCESS, message_offset);
            }
        }

        if (message[0] != '\0') {
            display_message(message, COLOR_ERROR, message_offset + violation_count + 1);
            message[0] = '\0';
        }

        refresh();
        int ch = getch();

        /* Handle user input */
        if (ch == KEY_UP) {
            cursor_y = (cursor_y - 1 + GRID_SIZE) % GRID_SIZE;
        } else if (ch == KEY_DOWN) {
            cursor_y = (cursor_y + 1) % GRID_SIZE;
        } else if (ch == KEY_LEFT) {
            cursor_x = (cursor_x - 1 + GRID_SIZE) % GRID_SIZE;
        } else if (ch == KEY_RIGHT) {
            cursor_x = (cursor_x + 1) % GRID_SIZE;
        } else if (ch == '\n' || ch == ' ') {
            if (is_cell_editable(state, cursor_y, cursor_x)) {
                if (state->grid[cursor_y][cursor_x] == EMPTY) {
                    state->grid[cursor_y][cursor_x] = SUN;
                } else if (state->grid[cursor_y][cursor_x] == SUN) {
                    state->grid[cursor_y][cursor_x] = MOON;
                } else {
                    state->grid[cursor_y][cursor_x] = EMPTY;
                }
            } else {
                snprintf(message, sizeof(message), "This cell cannot be modified.");
            }
        } else if (ch == 'r') {
            /* Reset the game */
            reset_game_state(state);
            break;
        } else if (ch == 's') {
            /* Show the solution */
            for (int i = 0; i < GRID_SIZE; i++) {
                for (int j = 0; j < GRID_SIZE; j++) {
                    state->grid[i][j] = state->solution_grid[i][j];
                }
            }
        } else if (ch == 'q') {
            endwin();
            exit(0);
        }

        if (game_won) {
            snprintf(message, sizeof(message), "Press 'r' to replay or 'q' to quit.");
        }
    }
}

void draw_game_grid(GameState *state, int cursor_x, int cursor_y) {
    int total_height = GRID_SIZE * (CELL_HEIGHT + 1) + 1;
    int total_width = GRID_SIZE * (CELL_WIDTH + 1) + 1;

    /* Draw the grid cells */
    for (int i = 0; i < total_height; i++) {
        for (int j = 0; j < total_width; j++) {
            int y = i;
            int x = j;

            if (i % (CELL_HEIGHT + 1) == 0) {
                /* Draw horizontal borders */
                if (j % (CELL_WIDTH + 1) == 0) {
                    mvaddch(y, x, ACS_PLUS);
                } else {
                    mvaddch(y, x, ACS_HLINE);
                }
            } else {
                if (j % (CELL_WIDTH + 1) == 0) {
                    /* Draw vertical borders */
                    mvaddch(y, x, ACS_VLINE);
                } else {
                    /* Inside a cell */
                    int cell_y = i / (CELL_HEIGHT + 1);
                    int cell_x = j / (CELL_WIDTH + 1);

                    /* Determine if the cell is under the cursor */
                    int is_cursor = (cell_y == cursor_y) && (cell_x == cursor_x);
                    int attr = A_NORMAL;
                    if (is_cursor) {
                        attr = A_REVERSE;
                    }

                    /* Relative position in the cell */
                    int rel_y = i % (CELL_HEIGHT + 1);
                    int rel_x = j % (CELL_WIDTH + 1);
                    int sym_y = (CELL_HEIGHT + 1) / 2;
                    int sym_x = (CELL_WIDTH + 1) / 2;

                    /* Draw the symbol or space */
                    if (rel_y == sym_y && rel_x == sym_x) {
                        char symbol = state->grid[cell_y][cell_x];
                        mvaddch(y, x, symbol | attr);
                    } else {
                        mvaddch(y, x, ' ' | attr);
                    }
                }
            }
        }
    }

    /* Draw horizontal signs */
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE - 1; j++) {
            char sign = state->signs_horizontal[i][j];
            if (sign != ' ') {
                int y = i * (CELL_HEIGHT + 1) + CELL_HEIGHT / 2 + 1;
                int x = (j + 1) * (CELL_WIDTH + 1);
                mvaddch(y, x, sign);
            }
        }
    }

    /* Draw vertical signs */
    for (int i = 0; i < GRID_SIZE - 1; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            char sign = state->signs_vertical[i][j];
            if (sign != ' ') {
                int y = (i + 1) * (CELL_HEIGHT + 1);
                int x = j * (CELL_WIDTH + 1) + CELL_WIDTH / 2 + 1;
                mvaddch(y, x, sign);
            }
        }
    }
}


void display_message(const char *message, int color_pair, int y_offset) {
    attron(COLOR_PAIR(color_pair));
    mvprintw(y_offset, 0, "%s", message);
    attroff(COLOR_PAIR(color_pair));
}

/** @file game_state.c
 *  @brief Implementation of game state management functions.
 */

#include "../inc/game_state.h"
#include "../inc/solver.h"
#include "../inc/utils.h"

void initialize_game_state(GameState *state) {
    reset_game_state(state);
}

void reset_game_state(GameState *state) {
    /* Generate a new puzzle */
    generate_full_solution(state->solution_grid);

    /* Copy the solution to the current grid */
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            state->grid[i][j] = state->solution_grid[i][j];
        }
    }

    /* Initialize signs */
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE - 1; j++) {
            state->signs_horizontal[i][j] = ' ';
        }
    }

    for (int i = 0; i < GRID_SIZE - 1; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            state->signs_vertical[i][j] = ' ';
        }
    }

    /* Place random signs */
    int num_signs = NUM_SIGNS_MIN + rand() % (NUM_SIGNS_MAX - NUM_SIGNS_MIN + 1);

    for (int n = 0; n < num_signs; n++) {
        int direction = rand() % 2;
        if (direction == 0) { /* Horizontal */
            int i = rand() % GRID_SIZE;
            int j = rand() % (GRID_SIZE - 1);
            if (state->solution_grid[i][j] == state->solution_grid[i][j + 1]) {
                state->signs_horizontal[i][j] = '=';
            } else {
                state->signs_horizontal[i][j] = 'X';
            }
        } else { /* Vertical */
            int i = rand() % (GRID_SIZE - 1);
            int j = rand() % GRID_SIZE;
            if (state->solution_grid[i][j] == state->solution_grid[i + 1][j]) {
                state->signs_vertical[i][j] = '=';
            } else {
                state->signs_vertical[i][j] = 'X';
            }
        }
    }

    /* Remove symbols to create the puzzle */
    int num_initial_symbols = NUM_INITIAL_SYMBOLS_MIN + rand() % (NUM_INITIAL_SYMBOLS_MAX - NUM_INITIAL_SYMBOLS_MIN + 1);
    int positions[GRID_SIZE * GRID_SIZE][2];
    int pos_count = 0;

    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            positions[pos_count][0] = i;
            positions[pos_count][1] = j;
            pos_count++;
        }
    }

    /* Shuffle positions */
    shuffle_positions(positions, pos_count);

    int symbols_to_remove = GRID_SIZE * GRID_SIZE - num_initial_symbols;

    for (int idx = 0; idx < pos_count && symbols_to_remove > 0; idx++) {
        int i = positions[idx][0];
        int j = positions[idx][1];
        char temp_symbol = state->grid[i][j];
        state->grid[i][j] = EMPTY;

        if (!has_violations(state->grid)) {
            symbols_to_remove--;
        } else {
            state->grid[i][j] = temp_symbol;
        }
    }

    /* Store the initial grid to track editable cells */
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            state->initial_grid[i][j] = state->grid[i][j];
        }
    }
}

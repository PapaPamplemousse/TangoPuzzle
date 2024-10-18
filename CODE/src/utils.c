/** @file utils.c
 *  @brief Implementation of utility functions.
 */

#include "../inc/utils.h"
#include "../inc/game_state.h"

int check_consecutive(char *sequence, int size) {
    int count = 0;
    char last_symbol = '\0';

    for (int i = 0; i < size; i++) {
        char symbol = sequence[i];
        if (symbol == last_symbol && symbol != EMPTY) {
            count++;
            if (count >= 2) {
                return 1;
            }
        } else {
            count = 0;
        }
        last_symbol = symbol;
    }
    return 0;
}

int is_grid_filled(char grid[GRID_SIZE][GRID_SIZE]) {
    int is_filled = 1;
    for (int i = 0; i < GRID_SIZE && is_filled; i++) {
        for (int j = 0; j < GRID_SIZE && is_filled; j++) {
            if (grid[i][j] == EMPTY) {
                is_filled = 0;
            }
        }
    }
    return is_filled;
}

int is_cell_editable(GameState *state, int row, int col) {
    return state->initial_grid[row][col] == EMPTY;
}

void shuffle_positions(int positions[][2], int count) {
    for (int i = count - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp0 = positions[i][0];
        int temp1 = positions[i][1];
        positions[i][0] = positions[j][0];
        positions[i][1] = positions[j][1];
        positions[j][0] = temp0;
        positions[j][1] = temp1;
    }
}

/** @brief Checks for rule violations and collects messages.
 *  @param state Pointer to the GameState structure.
 *  @param violations Array to store violation messages.
 *  @param violation_count Pointer to the violation count.
 */
void check_rules(GameState *state, char violations[100][100], int *violation_count) {
    int size = GRID_SIZE;
    int half = size / 2;
    char symbols[] = {SUN, MOON};
    *violation_count = 0;

    /* Check for consecutive symbols */
    for (int i = 0; i < size; i++) {
        if (check_consecutive(state->grid[i], size)) {
            snprintf(violations[*violation_count], 100, "More than two identical symbols consecutively in row %d.", i + 1);
            (*violation_count)++;
        }
        char col[GRID_SIZE];
        for (int j = 0; j < size; j++) {
            col[j] = state->grid[j][i];
        }
        if (check_consecutive(col, size)) {
            snprintf(violations[*violation_count], 100, "More than two identical symbols consecutively in column %d.", i + 1);
            (*violation_count)++;
        }
    }

    /* Check symbol counts */
    for (int idx = 0; idx < size; idx++) {
        char row[GRID_SIZE];
        char col[GRID_SIZE];
        for (int k = 0; k < size; k++) {
            row[k] = state->grid[idx][k];
            col[k] = state->grid[k][idx];
        }
        for (int s = 0; s < 2; s++) {
            char symbol = symbols[s];
            int count_row = 0, count_col = 0;
            for (int k = 0; k < size; k++) {
                if (row[k] == symbol) {
                    count_row++;
                }
                if (col[k] == symbol) {
                    count_col++;
                }
            }
            if (count_row > half) {
                snprintf(violations[*violation_count], 100, "Too many '%c' in row %d.", symbol, idx + 1);
                (*violation_count)++;
            }
            if (count_col > half) {
                snprintf(violations[*violation_count], 100, "Too many '%c' in column %d.", symbol, idx + 1);
                (*violation_count)++;
            }
        }
    }

    /* Check signs between cells */
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            char sign = state->signs_horizontal[i][j];
            if (sign == 'X' || sign == '=') {
                char cell1 = state->grid[i][j];
                char cell2 = state->grid[i][j + 1];
                if (cell1 != EMPTY && cell2 != EMPTY) {
                    if (sign == '=' && cell1 != cell2) {
                        snprintf(violations[*violation_count], 100, "Cells (%d,%d) and (%d,%d) must be identical.", i + 1, j + 1, i + 1, j + 2);
                        (*violation_count)++;
                    }
                    if (sign == 'X' && cell1 == cell2) {
                        snprintf(violations[*violation_count], 100, "Cells (%d,%d) and (%d,%d) must be different.", i + 1, j + 1, i + 1, j + 2);
                        (*violation_count)++;
                    }
                }
            }
        }
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size; j++) {
            char sign = state->signs_vertical[i][j];
            if (sign == 'X' || sign == '=') {
                char cell1 = state->grid[i][j];
                char cell2 = state->grid[i + 1][j];
                if (cell1 != EMPTY && cell2 != EMPTY) {
                    if (sign == '=' && cell1 != cell2) {
                        snprintf(violations[*violation_count], 100, "Cells (%d,%d) and (%d,%d) must be identical.", i + 1, j + 1, i + 2, j + 1);
                        (*violation_count)++;
                    }
                    if (sign == 'X' && cell1 == cell2) {
                        snprintf(violations[*violation_count], 100, "Cells (%d,%d) and (%d,%d) must be different.", i + 1, j + 1, i + 2, j + 1);
                        (*violation_count)++;
                    }
                }
            }
        }
    }
}

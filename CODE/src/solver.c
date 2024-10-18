/** @file solver.c
 *  @brief Implementation of puzzle solving functions.
 */

#include "../inc/solver.h"
#include "../inc/utils.h"

int generate_full_solution(char grid[GRID_SIZE][GRID_SIZE]) {
    int success = 0;
    while (!success) {
        /* Initialize the grid with empty cells */
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                grid[i][j] = EMPTY;
            }
        }

        if (solve_puzzle(grid)) {
            success = 1;
        }
    }
    return success;
}

int solve_puzzle(char grid[GRID_SIZE][GRID_SIZE]) {
    int row = -1, col = -1;
    int found_empty = 0;

    /* Find the first empty cell */
    for (int i = 0; i < GRID_SIZE && !found_empty; i++) {
        for (int j = 0; j < GRID_SIZE && !found_empty; j++) {
            if (grid[i][j] == EMPTY) {
                row = i;
                col = j;
                found_empty = 1;
            }
        }
    }

    if (!found_empty) {
        return 1; /* Puzzle is solved */
    }

    /* Try placing each symbol */
    char symbols[] = {SUN, MOON};
    for (int s = 0; s < 2; s++) {
        char symbol = symbols[s];
        if (is_valid_move(grid, row, col, symbol)) {
            grid[row][col] = symbol;
            if (solve_puzzle(grid)) {
                return 1;
            }
            grid[row][col] = EMPTY;
        }
    }

    return 0;
}

int is_valid_move(char grid[GRID_SIZE][GRID_SIZE], int row, int col, char symbol) {
    int is_valid = 1;
    char temp_row[GRID_SIZE];
    char temp_col[GRID_SIZE];
    int symbol_count = 0;

    /* Check row */
    for (int k = 0; k < GRID_SIZE; k++) {
        temp_row[k] = grid[row][k];
    }
    temp_row[col] = symbol;
    if (check_consecutive(temp_row, GRID_SIZE)) {
        is_valid = 0;
    }

    /* Check column */
    for (int k = 0; k < GRID_SIZE; k++) {
        temp_col[k] = grid[k][col];
    }
    temp_col[row] = symbol;
    if (check_consecutive(temp_col, GRID_SIZE)) {
        is_valid = 0;
    }

    /* Check symbol count in row */
    symbol_count = 0;
    for (int k = 0; k < GRID_SIZE; k++) {
        if (temp_row[k] == symbol) {
            symbol_count++;
        }
    }
    if (symbol_count > GRID_SIZE / 2) {
        is_valid = 0;
    }

    /* Check symbol count in column */
    symbol_count = 0;
    for (int k = 0; k < GRID_SIZE; k++) {
        if (temp_col[k] == symbol) {
            symbol_count++;
        }
    }
    if (symbol_count > GRID_SIZE / 2) {
        is_valid = 0;
    }

    return is_valid;
}

int has_violations(char grid[GRID_SIZE][GRID_SIZE]) {
    int size = GRID_SIZE;
    int half = size / 2;
    char symbols[] = {SUN, MOON};
    int violations = 0;

    /* Check rows and columns */
    for (int idx = 0; idx < size; idx++) {
        char row[GRID_SIZE];
        char col[GRID_SIZE];

        for (int k = 0; k < size; k++) {
            row[k] = grid[idx][k];
            col[k] = grid[k][idx];
        }

        if (check_consecutive(row, size)) {
            violations = 1;
        }
        if (check_consecutive(col, size)) {
            violations = 1;
        }

        /* Check symbol counts */
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

            if (count_row > half || count_col > half) {
                violations = 1;
            }
        }
    }

    return violations;
}

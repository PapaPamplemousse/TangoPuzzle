/** @file utils.h
 *  @brief Header file for utility functions and definitions.
 */

#ifndef UTILS_H
#define UTILS_H

#include "definitions.h"

/** Forward declaration of struct GameState */
struct GameState;

/** @brief Checks for consecutive identical symbols in a sequence.
 *  @param sequence The sequence to check.
 *  @param size The size of the sequence.
 *  @return Returns 1 if there are consecutive symbols, 0 otherwise.
 */
int check_consecutive(char *sequence, int size);

/** @brief Checks if the grid is completely filled.
 *  @param grid The current grid.
 *  @return Returns 1 if the grid is filled, 0 otherwise.
 */
int is_grid_filled(char grid[GRID_SIZE][GRID_SIZE]);

/** @brief Checks if a cell is editable by the player.
 *  @param state Pointer to the GameState structure.
 *  @param row The row index.
 *  @param col The column index.
 *  @return Returns 1 if the cell is editable, 0 otherwise.
 */
int is_cell_editable(struct GameState *state, int row, int col);

/** @brief Shuffles an array of positions.
 *  @param positions The array of positions.
 *  @param count The number of positions.
 */
void shuffle_positions(int positions[][2], int count);

/** @brief Checks for rule violations and collects messages.
 *  @param state Pointer to the GameState structure.
 *  @param violations Array to store violation messages.
 *  @param violation_count Pointer to the violation count.
 */
void check_rules(struct GameState *state, char violations[100][100], int *violation_count);

#endif // UTILS_H

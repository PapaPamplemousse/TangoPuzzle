/** @file solver.h
 *  @brief Header file for puzzle solving functions.
 */

#ifndef SOLVER_H
#define SOLVER_H

#include "definitions.h"

/** Forward declaration of struct GameState */
struct GameState;

/** @brief Generates a full solution for the puzzle.
 *  @param grid The grid to fill with the solution.
 *  @return Returns 1 if successful, 0 otherwise.
 */
int generate_full_solution(char grid[GRID_SIZE][GRID_SIZE]);

/** @brief Solves the puzzle using backtracking.
 *  @param grid The grid to solve.
 *  @return Returns 1 if a solution is found, 0 otherwise.
 */
int solve_puzzle(char grid[GRID_SIZE][GRID_SIZE]);

/** @brief Checks if placing a symbol at a position is valid.
 *  @param grid The current grid.
 *  @param row The row index.
 *  @param col The column index.
 *  @param symbol The symbol to place.
 *  @return Returns 1 if valid, 0 otherwise.
 */
int is_valid_move(char grid[GRID_SIZE][GRID_SIZE], int row, int col, char symbol);

/** @brief Checks if the grid has any violations of the rules.
 *  @param grid The current grid.
 *  @return Returns 1 if there are violations, 0 otherwise.
 */
int has_violations(char grid[GRID_SIZE][GRID_SIZE]);

#endif // SOLVER_H

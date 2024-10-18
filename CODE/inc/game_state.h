/** @file game_state.h
 *  @brief Header file for game state management.
 */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "definitions.h"

/** @brief Represents the game state including the grid and signs. */
typedef struct GameState {
    char grid[GRID_SIZE][GRID_SIZE];
    char signs_horizontal[GRID_SIZE][GRID_SIZE - 1];
    char signs_vertical[GRID_SIZE - 1][GRID_SIZE];
    char initial_grid[GRID_SIZE][GRID_SIZE];
    char solution_grid[GRID_SIZE][GRID_SIZE];
} GameState;

/** @brief Initializes the game state.
 *  @param state Pointer to the GameState structure.
 */
void initialize_game_state(GameState *state);

/** @brief Resets the game state to start a new game.
 *  @param state Pointer to the GameState structure.
 */
void reset_game_state(GameState *state);

#endif // GAME_STATE_H

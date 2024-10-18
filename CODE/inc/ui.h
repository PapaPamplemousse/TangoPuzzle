/** @file ui.h
 *  @brief Header file for user interface functions.
 */

#ifndef UI_H
#define UI_H

#include "game_state.h"

/** @brief Main game loop handling user interaction.
 *  @param state Pointer to the GameState structure.
 */
void main_game_loop(GameState *state);

/** @brief Draws the game grid on the screen.
 *  @param state Pointer to the GameState structure.
 *  @param cursor_x X-coordinate of the cursor.
 *  @param cursor_y Y-coordinate of the cursor.
 */
void draw_game_grid(GameState *state, int cursor_x, int cursor_y);

/** @brief Displays messages to the player.
 *  @param message The message to display.
 *  @param color_pair The color pair to use.
 *  @param y_offset The vertical offset for the message.
 */
void display_message(const char *message, int color_pair, int y_offset);

#endif // UI_H

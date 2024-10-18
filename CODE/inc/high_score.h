/** @file high_score.h
 *  @brief Header file for high score management.
 */

#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include "definitions.h"
#include <stdio.h>

#define MAX_HIGH_SCORES 10
#define HIGH_SCORE_FILE "high_scores.txt"

/** @brief Structure to hold a high score entry. */
typedef struct {
    char player_name[50];
    double time_seconds;
} HighScoreEntry;

/** @brief Loads high scores from the file.
 *  @param high_scores Array to store the high scores.
 *  @param count Pointer to store the number of high scores loaded.
 */
void load_high_scores(HighScoreEntry high_scores[], int *count);

/** @brief Saves high scores to the file.
 *  @param high_scores Array of high scores to save.
 *  @param count Number of high scores.
 */
void save_high_scores(HighScoreEntry high_scores[], int count);

/** @brief Adds a new high score if it qualifies.
 *  @param high_scores Array of current high scores.
 *  @param count Pointer to the number of high scores.
 *  @param new_score The new score to consider.
 */
void add_high_score(HighScoreEntry high_scores[], int *count, HighScoreEntry new_score);

/** @brief Displays the high scores on the screen.
 *  @param high_scores Array of high scores.
 *  @param count Number of high scores.
 *  @param y_offset Vertical offset for display.
 */
void display_high_scores(HighScoreEntry high_scores[], int count, int y_offset);

#endif // HIGH_SCORE_H

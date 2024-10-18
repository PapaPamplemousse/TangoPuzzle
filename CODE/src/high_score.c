/** @file high_score.c
 *  @brief Implementation of high score management functions.
 */

#include "../inc/high_score.h"
#include <string.h>

void load_high_scores(HighScoreEntry high_scores[], int *count) {
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    *count = 0;

    if (file != NULL) {
        while (fscanf(file, "%49s %lf", high_scores[*count].player_name, &high_scores[*count].time_seconds) == 2 && *count < MAX_HIGH_SCORES) {
            (*count)++;
        }
        fclose(file);
    }
}

void save_high_scores(HighScoreEntry high_scores[], int count) {
    FILE *file = fopen(HIGH_SCORE_FILE, "w");

    if (file != NULL) {
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s %.2f\n", high_scores[i].player_name, high_scores[i].time_seconds);
        }
        fclose(file);
    }
}

void add_high_score(HighScoreEntry high_scores[], int *count, HighScoreEntry new_score) {
    // Insert the new score in the sorted array
    int i = *count - 1;
    while (i >= 0 && high_scores[i].time_seconds > new_score.time_seconds && i < MAX_HIGH_SCORES - 1) {
        high_scores[i + 1] = high_scores[i];
        i--;
    }
    if (i < MAX_HIGH_SCORES - 1) {
        high_scores[i + 1] = new_score;
        if (*count < MAX_HIGH_SCORES) {
            (*count)++;
        }
    }
}

void display_high_scores(HighScoreEntry high_scores[], int count, int y_offset) {
    attron(COLOR_PAIR(3)); // Using a different color pair for high scores
    mvprintw(y_offset, 0, "High Scores:");
    for (int i = 0; i < count; i++) {
        mvprintw(y_offset + i + 1, 0, "%d. %s - %.2f seconds", i + 1, high_scores[i].player_name, high_scores[i].time_seconds);
    }
    attroff(COLOR_PAIR(3));
}

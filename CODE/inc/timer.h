/** @file timer.h
 *  @brief Header file for timer functions.
 */

#ifndef TIMER_H
#define TIMER_H

#include "definitions.h"
#include <time.h>

/** @brief Timer structure to keep track of time. */
typedef struct {
    time_t start_time;
    time_t end_time;
} Timer;

/** @brief Starts the timer.
 *  @param timer Pointer to the Timer structure.
 */
void start_timer(Timer *timer);

/** @brief Stops the timer.
 *  @param timer Pointer to the Timer structure.
 */
void stop_timer(Timer *timer);

/** @brief Calculates the elapsed time in seconds.
 *  @param timer Pointer to the Timer structure.
 *  @return The elapsed time in seconds.
 */
double get_elapsed_time(Timer *timer);

#endif // TIMER_H

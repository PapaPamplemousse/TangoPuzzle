/** @file timer.c
 *  @brief Implementation of timer functions.
 */

#include "../inc/timer.h"

void start_timer(Timer *timer) {
    timer->start_time = time(NULL);
}

void stop_timer(Timer *timer) {
    timer->end_time = time(NULL);
}

double get_elapsed_time(Timer *timer) {
    return difftime(timer->end_time, timer->start_time);
}

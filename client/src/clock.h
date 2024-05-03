#ifndef _CLOCK_
#define _CLOCK_

#include <stdbool.h>

typedef struct clock Clock;
typedef struct timer Timer;

Clock *create_clock();
Timer *create_timer(Clock *clock, int interval);
bool timer_finished(Timer *timer);

/*
 * Gets the current delta time
 */
int get_clock_deltatime(Clock *clock);

/*
 * Updates the clock deltatime
 */
void update_clock(Clock *clock);

#endif // !_CLOCK_

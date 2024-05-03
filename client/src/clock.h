#ifndef _CLOCK_
#define _CLOCK_

typedef struct clock Clock;

Clock *create_clock();

/*
 * Gets the current delta time
 */
int get_clock_deltatime(Clock *clock);

/*
 * Updates the clock deltatime
 */
void update_clock(Clock *clock);

#endif // !_CLOCK_

#include <SDL2/SDL_timer.h>
#include <stdlib.h>
typedef struct {
  int previousTicks;
  int deltaTime;
} Clock;

Clock *create_clock() {
  Clock *clock = malloc(sizeof(Clock));
  clock->previousTicks = SDL_GetTicks();
  clock->deltaTime = 0;
  return clock;
}

int get_clock_deltatime(Clock *clock) { return clock->deltaTime; }

void update_clock(Clock *clock) {
  int tick = SDL_GetTicks();
  clock->deltaTime = tick - clock->previousTicks;
  clock->previousTicks = tick;
}

void destroy_clock(Clock *clock) {
  if (clock) {
    free(clock);
    clock = NULL;
  }
}

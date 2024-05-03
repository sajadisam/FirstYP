#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int interval;
  int passed;
} Timer;

typedef struct {
  int previousTicks;
  int deltaTime;
  Timer **timers;
  int timers_len;
} Clock;

Clock *create_clock() {
  Clock *clock = malloc(sizeof(Clock));
  clock->previousTicks = SDL_GetTicks();
  clock->deltaTime = 0;
  clock->timers = malloc(sizeof(Timer *));
  clock->timers_len = 0;
  return clock;
}

Timer *create_timer(Clock *clock, int interval) {
  Timer *timestop = malloc(sizeof(Timer));
  timestop->interval = interval;
  timestop->passed = 0;
  clock->timers =
      realloc(clock->timers, sizeof(Timer *) * clock->timers_len + 1);
  clock->timers[clock->timers_len] = timestop;
  clock->timers_len++;
  return timestop;
}

bool timer_finished(Timer *timestop) {
  if (timestop->passed >= timestop->interval) {
    timestop->passed = 0;
    return true;
  }
  return false;
}

int get_clock_deltatime(Clock *clock) { return clock->deltaTime; }

void update_clock(Clock *clock) {
  int tick = SDL_GetTicks();
  clock->deltaTime = tick - clock->previousTicks;
  clock->previousTicks = tick;
  for (int i = 0; i < clock->timers_len; i++) {
    Timer *timestop = clock->timers[i];
    timestop->passed += clock->deltaTime;
  }
}

void destroy_clock(Clock *clock) {
  if (clock) {
    free(clock);
    clock = NULL;
  }
}

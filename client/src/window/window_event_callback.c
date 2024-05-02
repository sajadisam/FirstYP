#include "../shared/debug.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

/*
 * A callback that gets triggered based on window event
 */
void *window_event_callback(SDL_Event *event, void *arg) {
  if (event->type == SDL_QUIT) {
    DEBUG("Closing the window\n");
    return (void *)true;
  }
  return (void *)false;
}

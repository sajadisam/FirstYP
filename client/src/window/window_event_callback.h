#ifndef _WINDOW_EVENT_CALLBACK
#define _WINDOW_EVENT_CALLBACK

#include <SDL2/SDL.h>

/*
 * A callback that gets triggered based on window event
 */
void *window_event_callback(const SDL_Event *event, void *arg);

#endif // !_WINDOW_EVENT_CALLBACK

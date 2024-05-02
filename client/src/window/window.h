#ifndef _WINDOW_
#define _WINDOW_

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

typedef struct window Window;

SDL_Renderer *get_window_renderer(Window *window);
SDL_Window *get_window_sdlwindow(Window *window);

typedef void *(*EventLoopCallback)(SDL_Event *event, void *);

Window *window_create(const char *name, int width, int height);

void window_destroy(Window *window);

/*
 *  Handles a single window event by passing it to the callback
 *
 *  @arg window: Window to listen on the events
 *  @arg callback: callback to send the events to
 *  @arg arg: additional argument to be passed to the callback
 *  @return the value
 */
void *window_event_loop(Window *window, EventLoopCallback callback, void *arg);

#endif // !_WINDOW_

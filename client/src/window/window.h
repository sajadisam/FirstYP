#ifndef _WINDOW_
#define _WINDOW_

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

typedef struct window Window;
typedef void *(*EventLoopCallback)(const SDL_Event *event, void *);

/*
 * Creates a window
 */
Window *window_create(const char *name, const int width, const int height);
void window_destroy(Window *window);

/*
 *  Handles a single window event by passing it to the callback
 *
 *  @arg window: Window to listen on the events
 *  @arg callback: callback to send the events to
 *  @arg arg: additional argument to be passed to the callback
 *  @return the value
 */
void *window_event_loop(Window *window, const EventLoopCallback callback,
                        void *arg);

SDL_Renderer *get_window_renderer(const Window *window);
SDL_Window *get_window_sdlwindow(const Window *window);

#endif // !_WINDOW_

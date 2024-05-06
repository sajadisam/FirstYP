#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>

typedef struct window Window;
typedef int (*EventLoopCallback)(const SDL_Event *event, void *);

Window *window_create(const char *name, const int width, const int height);
void window_destroy(Window *window);

int window_event_loop(const Window *window, EventLoopCallback callback,
                      void *arg);

void set_window_mouse_coordinate(Window *window, SDL_Point coordinate);
SDL_Point get_window_mouse_coordinate(Window *window);
SDL_Renderer *get_window_renderer(const Window *window);
SDL_Window *get_window_sdlwindow(const Window *window);

int window_get_width(Window const *window);
int window_get_height(Window const *window);

#endif // WINDOW_H

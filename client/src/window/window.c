#include "../../../lib/misc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

typedef struct {
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
  SDL_Point mouse_coordinate;
  int is_fullscreen;
} Window;

typedef int (*EventLoopCallback)(const SDL_Event *event, void *);

Window *window_create(const char *name, const int width, const int height) {
  SDL_Window *pWindow =
      SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, NULL);

  if (!pWindow)
    on_sdl_error();

  const int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow, -1, flags);

  if (!pRenderer) {
    SDL_DestroyWindow(pWindow);
    on_sdl_error();
  }

  Window *window = malloc(sizeof(Window));
  window->m_Window = pWindow;
  window->m_Renderer = pRenderer;
  window->mouse_coordinate = (SDL_Point){-1, -1};
  window->is_fullscreen = 0;
  return window;
}

void window_destroy(Window *window) {
  if (window) {
    SDL_DestroyRenderer(window->m_Renderer);
    SDL_DestroyWindow(window->m_Window);
    free(window);
    window = NULL;
  }
}

int window_event_loop(const Window *window, const EventLoopCallback callback,
                      void *arg) {
  SDL_Event event;
  while (SDL_PollEvent(&event) > 0) {
    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F11) {
      Window *w = (Window *)window;
      if (w->is_fullscreen) {
        SDL_SetWindowFullscreen(w->m_Window, 0);
        w->is_fullscreen = 0;
      } else {
        SDL_SetWindowFullscreen(w->m_Window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        w->is_fullscreen = 1;
      }
    }
    int callbackResult = (int)callback(&event, arg);
    if (callbackResult) {
      return callbackResult;
    }
  }
  return 0;
}

void set_window_mouse_coordinate(Window *window, SDL_Point coordinate) {
  window->mouse_coordinate = coordinate;
}

SDL_Point get_window_mouse_coordinate(Window *window) {
  return window->mouse_coordinate;
}

SDL_Renderer *get_window_renderer(const Window *window) {
  return window->m_Renderer;
}
SDL_Window *get_window_sdlwindow(const Window *window) {
  return window->m_Window;
}

int window_get_width(Window const *window) {
  int width, height;
  SDL_GetWindowSize(window->m_Window, &width, &height);
  return width;
}

int window_get_height(Window const *window) {
  int width, height;
  SDL_GetWindowSize(window->m_Window, &width, &height);
  return height;
}

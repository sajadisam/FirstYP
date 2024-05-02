#include "../shared/debug.h"
#include "../shared/misc.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>

typedef struct {
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
} Window;

typedef void *(*EventLoopCallback)(SDL_Event *event, void *);

/* GETTERS & SETTERS */
SDL_Renderer *get_window_renderer(Window *window) { return window->m_Renderer; }
SDL_Window *get_window_sdlwindow(Window *window) { return window->m_Window; }

Window *window_create(const char *name, int width, int height) {
  INFO("Creating a window\n");

  SDL_Window *pWindow =
      SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       width, height, SDL_WINDOW_RESIZABLE);

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
  return window;
}

void window_destroy(Window *window) {
  SDL_DestroyRenderer(window->m_Renderer);
  SDL_DestroyWindow(window->m_Window);
  free(window);
}

void *window_event_loop(Window *window, EventLoopCallback callback, void *arg) {
  SDL_Event event;
  while (SDL_PollEvent(&event) > 0) {
    void *callbackResult = callback(&event, arg);
    if (callbackResult) {
      return callbackResult;
    }
  }
  return NULL;
}

#include "window.h"
#include "debug.h"
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

void PrintSdlError() { ERR("%s\n", SDL_GetError()); }

bool Window_IntitializeSDL() { return SDL_Init(SDL_INIT_VIDEO) != 0; }

// TODO(Sajad) improve error handling
Window *Window_Create(const char *name, int width, int height) {
  INFO("Creating a window\n");

  SDL_Window *pWindow = SDL_CreateWindow(
      name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);

  if (!pWindow) {
    PrintSdlError();
    SDL_Quit();
    return NULL;
  }

  const int flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow, -1, flags);

  if (!pRenderer) {
    PrintSdlError();
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return NULL;
  }

  Window *window = malloc(sizeof(Window));
  window->m_Window = pWindow;
  window->m_Renderer = pRenderer;
  return window;
}

void Window_Destroy(Window *wnd) {
  SDL_DestroyRenderer(wnd->m_Renderer);
  SDL_DestroyWindow(wnd->m_Window);
  free(wnd);
}

SDL_Texture *Window_Texture(const char *path, Window *wnd) {
  SDL_Surface *pSurface = IMG_Load(path);
  if (!pSurface) {
    PrintSdlError();
    return NULL;
  }
  SDL_Texture *pTexture =
      SDL_CreateTextureFromSurface(wnd->m_Renderer, pSurface);
  SDL_FreeSurface(pSurface);
  if (!pTexture) {
    PrintSdlError();
    return NULL;
  }

  return pTexture;
}

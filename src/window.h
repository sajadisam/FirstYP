#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

struct {
  SDL_Window *m_Window;
  SDL_Renderer *m_Renderer;
} typedef Window;

bool Window_IntitializeSDL();
Window *Window_Create(const char *name, int width, int height);
void Window_Destroy(Window *wnd);
SDL_Texture *Window_Texture(const char *path, Window *wnd);

#endif

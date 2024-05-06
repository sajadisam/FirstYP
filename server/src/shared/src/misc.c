#include "debug.h"
#include <SDL2/SDL.h>

void on_sdl_error() {
  ERR("%s\n", SDL_GetError());
  SDL_Quit();
  exit(5);
}

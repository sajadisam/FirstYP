#include "debug.h"
#include <SDL2/SDL.h>

void on_sdl_error() {
  ERR("%s\n", SDL_GetError());
  SDL_Quit();
  exit(5);
}

int randomi32(int min, int max) { return rand() % (max + 1 - min) + min; }

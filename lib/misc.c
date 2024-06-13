#include "debug.h"
#include <SDL2/SDL.h>

void on_sdl_error() {
  ERR("%s\n", SDL_GetError());
  SDL_Quit();
  exit(5);
}

int randomi32(int min, int max) { return rand() % (max + 1 - min) + min; }

float clamp(float value, float min, float max) {
  const double t = value < min ? min : value;
  return t > max ? max : t;
}

float vector_length(int x, int y) { return sqrt(x * x + y * y); }

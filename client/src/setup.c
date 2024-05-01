#include "../../shared/include/debug.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <stdbool.h>
#include <stdlib.h>

void initalize_sdl() {
  if (SDL_Init(SDL_INIT_VIDEO) == -1 || (SDLNet_Init() == -1)) {
    ERR("%s\n", SDL_GetError());
    exit(1);
  }
}

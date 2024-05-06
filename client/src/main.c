#include "SDL2/SDL.h"
#include "SDL2/SDL_net.h"
#include "debug.h"
#include "game.h"

#undef main

int main() {
  if (SDL_Init(SDL_INIT_EVERYTHING) == -1 || (SDLNet_Init() == -1)) {
    ERR("Failed to initialize SDL\n");
    exit(1);
  }
  Window *window = window_create("Zombie Hunter", 800, 600);
  Game *game = game_create(window);
  game_run(game);
  game_destroy(game);
}

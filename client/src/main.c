#include "../../shared/include/debug.h"
#include "config.h"
#include "game.h"
#include "player/player.h"
#include "setup.h"
#include "window/window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

/*
 * A callback that gets triggered based on window event
 */
void *window_event_callback(SDL_Event *event, void *arg) {
  if (event->type == SDL_QUIT) {
    DEBUG("Closing the window\n");
    return true;
  }
  return false;
}

int main() {
  initalize_sdl();
  Window *window = window_create("Zombie hunter", WINDOW_WIDTH, WINDOW_HEIGHT);
  Player *player = create_player();
  Game *game = create_game(window, player);
  while (true) {
    if (window_event_loop(window, window_event_callback, NULL))
      break;
    SDL_RenderClear(get_game_renderer(game));
    SDL_RenderPresent(get_game_renderer(game));
  }
}

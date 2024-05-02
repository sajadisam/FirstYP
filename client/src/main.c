#include "config.h"
#include "game.h"
#include "player/player.h"
#include "setup.h"
#include "ui/sprite.h"
#include "window/window.h"
#include "window/window_event_callback.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <stdbool.h>

int main() {
  initalize_sdl();
  Window *window = window_create("Zombie hunter", WINDOW_WIDTH, WINDOW_HEIGHT);
  Player *player = create_player();
  Sprite *sprite =
      create_sprite(window, "./resources/player.png", (SDL_Point){100, 100});
  Game *game = create_game(window, player);
  while (true) {
    if (window_event_loop(window, window_event_callback, NULL))
      break;
    render_sprite_loop(game, sprite);
  }
}

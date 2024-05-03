#include "game.h"
#include "player/player.h"
#include "shared/config.h"
#include "ui/sprite.h"
#include "ui/spritesheet.h"
#include "window/window.h"
#include "window/window_event_callback.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

int main() {
  Window *window = window_create("Zombie hunter", WINDOW_WIDTH, WINDOW_HEIGHT);
  Player *player = create_player();
  SpriteSheet *playerSprite =
      create_spritesheet(window, "./resources/old_player.png", 3, 3);
  Sprite *mapSprite = create_sprite(window, "./resources/map.png");
  Game *game = create_game(window, player);
  while (!window_event_loop(window, window_event_callback, game)) {
    SDL_RenderClear(get_game_renderer(game));
    render_sprite(game, mapSprite, (Size){0, 0}, (SDL_Point){0, 0});
    render_spritesheet(game, playerSprite, (Size){10, 10}, (SDL_Point){20, 20});
    SDL_RenderPresent(get_game_renderer(game));
  }
}

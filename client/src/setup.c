#include "clock.h"
#include "game.h"
#include "player/player.h"
#include "shared/config.h"
#include "shared/debug.h"
#include "ui/sprite.h"
#include "ui/spritesheet.h"
#include "window/window.h"
#include "window/window_event_callback.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <stdbool.h>
#include <stdlib.h>

void initialize_sdl() {
  if (SDL_Init(SDL_INIT_VIDEO) == -1 || (SDLNet_Init() == -1)) {
    ERR("%s\n", SDL_GetError());
    exit(1);
  }
}

Game *initialize() {
  initialize_sdl();
  Window *window = window_create("Zombie hunter", WINDOW_WIDTH, WINDOW_HEIGHT);
  SpriteSheet *playerSprite =
      create_spritesheet(window, "./resources/player.png", 4, 4);
  Sprite *mapSprite = create_sprite(window, "./resources/new_map.png");
  Player *player = create_player((void *)playerSprite);
  set_player_coordinates(player,
                         (SDL_Point){WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2});
  Clock *clock = create_clock();
  Game *game = create_game(window, player, clock);
  set_sprite_render_size(mapSprite, (Size){WINDOW_WIDTH, WINDOW_HEIGHT});
  add_game_sprite(game, (void *)mapSprite, "map");
  add_game_sprite(game, get_spritesheet_sprite(playerSprite), "player");
  return game;
}

void run(Game *game) {
  Window *window = get_game_window(game);
  Player *player = get_game_player(game);
  Clock *clock = get_game_clock(game);
  Timer *animation_speed = create_timer(clock, 100);
  while (!window_event_loop(window, window_event_callback, game)) {
    update_clock(clock);
    perform_movement(player, animation_speed);
    render_game_sprites(game);
  }
}

void shutdown(Game *game) { DEBUG("Closing the window\n"); }

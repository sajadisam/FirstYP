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

void initalize_sdl() {
  if (SDL_Init(SDL_INIT_VIDEO) == -1 || (SDLNet_Init() == -1)) {
    ERR("%s\n", SDL_GetError());
    exit(1);
  }
}

Game *initialize() {
  Window *window = window_create("Zombie hunter", WINDOW_WIDTH, WINDOW_HEIGHT);
  Player *player = create_player(
      (void *)create_spritesheet(window, "./resources/player.png", 4, 4));
  Sprite *mapSprite = create_sprite(window, "./resources/new_map.png");
  Clock *clock = create_clock();
  Game *game = create_game(window, player, (void *)mapSprite, clock);
  return game;
}

void run(Game *game) {
  int deltaTime;
  Window *window = get_game_window(game);
  Player *player = get_game_player(game);
  Clock *clock = get_game_clock(game);
  while (!window_event_loop(window, window_event_callback, game)) {
    update_clock(clock);
    SDL_RenderClear(get_game_renderer(game));
    render_sprite(game, get_game_map(game), (Size){0, 0}, (SDL_Point){0, 0});
    render_spritesheet(game, (SpriteSheet *)get_player_spritesheet(player),
                       (Size){10, 10}, (SDL_Point){20, 20});
    SDL_RenderPresent(get_game_renderer(game));
    printf("deltatime: %d\n", get_clock_deltatime(clock));
  }
}

void shutdown(Game *game) {
  // shutdown
}

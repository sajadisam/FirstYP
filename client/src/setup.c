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
#include <stdio.h>
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
  DEBUG("playerflag: %d\n", (int)get_player_flags(player));
  return game;
}

void run(Game *game) {
  Window *window = get_game_window(game);
  Player *player = get_game_player(game);
  Clock *clock = get_game_clock(game);
  Timer *second = create_timer(clock, 1000);
  while (!window_event_loop(window, window_event_callback, game)) {
    update_clock(clock);
    PlayerFlag flags = get_player_flags(player);
    if (flags & MOVINGUP)
      player_move_up(player);
    if (flags & MOVINGDOWN)
      player_move_down(player);
    if (flags & MOVINGRIGHT)
      player_move_right(player);
    if (flags & MOVINGLEFT)
      player_move_left(player);

    if (timer_finished(second))
      printf("deltatime: %d\n", get_clock_deltatime(clock));
    SDL_RenderClear(get_game_renderer(game));
    render_sprite(game, get_game_map(game), (Size){0, 0}, (SDL_Point){0, 0});
    render_spritesheet(game, (SpriteSheet *)get_player_spritesheet(player),
                       (Size){20, 20}, get_player_coordinates(player));
    SDL_RenderPresent(get_game_renderer(game));
  }
}

void shutdown(Game *game) { DEBUG("Closing the window\n"); }

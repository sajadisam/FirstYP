#include "clock.h"
#include "player/player.h"
#include "ui/sprite.h"
#include "window/window.h"

typedef struct {
  Window *window;
  Player *player;
  Sprite *map;
  Clock *clock;
} Game;

Game *create_game(Window *window, Player *player, Sprite *map, Clock *clock) {
  Game *game = malloc(sizeof(Game));
  game->window = window;
  game->player = player;
  game->map = map;
  game->clock = clock;
  return game;
}

SDL_Renderer *get_game_renderer(const Game *game) {
  return get_window_renderer(game->window);
}
Window *get_game_window(const Game *game) { return game->window; }
Player *get_game_player(const Game *game) { return game->player; }
Sprite *get_game_map(const Game *game) { return game->map; }
Clock *get_game_clock(const Game *game) { return game->clock; }

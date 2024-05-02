#include "player/player.h"
#include "window/window.h"
#include <stdlib.h>

typedef struct {
  Window *window;
  Player *player;
} Game;

/* GETTERS & SETTERS */

SDL_Renderer *get_game_renderer(Game *game) {
  return get_window_renderer(game->window);
}

SDL_Window *get_game_sdlwindow(Game *game) {
  return get_window_sdlwindow(game->window);
}

Game *create_game(Window *window, Player *player) {
  Game *game = malloc(sizeof(Game));
  game->window = window;
  game->player = player;
  return game;
}

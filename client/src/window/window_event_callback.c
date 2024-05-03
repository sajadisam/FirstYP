#include "../game.h"
#include "../shared/debug.h"
#include "../ui/spritesheet.h"
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>

/*
 * A callback that gets triggered based on window event
 */
void *window_event_callback(SDL_Event *event, void *arg) {
  if (event->type == SDL_QUIT)
    return true;
  Game *game = arg;
  Player *player = get_game_player(game);
  PlayerFlag flags = get_player_flags(player);

  switch (event->type) {
  case SDL_KEYDOWN:
    if (event->key.keysym.scancode == SDL_SCANCODE_UP)
      flags |= MOVINGUP;
    if (event->key.keysym.scancode == SDL_SCANCODE_DOWN)
      flags |= MOVINGDOWN;
    if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
      flags |= MOVINGRIGHT;
    if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
      flags |= MOVINGLEFT;
    break;
  case SDL_KEYUP:
    if (event->key.keysym.scancode == SDL_SCANCODE_UP)
      flags &= ~MOVINGUP;
    if (event->key.keysym.scancode == SDL_SCANCODE_DOWN)
      flags &= ~MOVINGDOWN;
    if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT)
      flags &= ~MOVINGRIGHT;
    if (event->key.keysym.scancode == SDL_SCANCODE_LEFT)
      flags &= ~MOVINGLEFT;
    break;
  }
  set_player_flags(player, flags);
  return false;
}

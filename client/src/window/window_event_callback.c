#include "../game.h"
#include "../ui/spritesheet.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <stdbool.h>

/*
 * A callback that gets triggered based on window event
 */
void *window_event_callback(const SDL_Event *event, void *arg) {
  if (event->type == SDL_QUIT)
    return true;
  Game *game = arg;
  Player *player = get_game_player(game);
  PlayerFlag flags = get_player_flags(player);
  switch (event->type) {
  case SDL_MOUSEMOTION:
    set_window_mouse_coordinate(get_game_window(game),
                                (SDL_Point){event->motion.x, event->motion.y});
    break;
  case SDL_KEYDOWN: {
    SDL_Scancode code = event->key.keysym.scancode;
    if (code == SDL_SCANCODE_UP || code == SDL_SCANCODE_W)
      flags |= MOVINGUP;
    if (code == SDL_SCANCODE_DOWN || code == SDL_SCANCODE_S)
      flags |= MOVINGDOWN;
    if (code == SDL_SCANCODE_RIGHT || code == SDL_SCANCODE_D)
      flags |= MOVINGRIGHT;
    if (code == SDL_SCANCODE_LEFT || code == SDL_SCANCODE_A)
      flags |= MOVINGLEFT;
  } break;
  case SDL_KEYUP: {
    SDL_Scancode code = event->key.keysym.scancode;
    if (code == SDL_SCANCODE_UP || code == SDL_SCANCODE_W)
      flags &= ~MOVINGUP;
    if (code == SDL_SCANCODE_DOWN || code == SDL_SCANCODE_S)
      flags &= ~MOVINGDOWN;
    if (code == SDL_SCANCODE_RIGHT || code == SDL_SCANCODE_D)
      flags &= ~MOVINGRIGHT;
    if (code == SDL_SCANCODE_LEFT || code == SDL_SCANCODE_A)
      flags &= ~MOVINGLEFT;
  } break;
  }
  set_player_flags(player, flags);
  return false;
}

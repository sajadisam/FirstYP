#ifndef _PLAYER_
#define _PLAYER_

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct {
  bool up, down, left, right;
} PlayerMovementFlags;

typedef struct {
  PlayerMovementFlags movement_flags;
} Player;

void Player_Events(SDL_Event *event, Player *player);

#endif // !_PLAYER_

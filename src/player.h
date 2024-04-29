#ifndef _PLAYER_
#define _PLAYER_

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

typedef struct {
  bool up, down, left, right;
} PlayerMovementFlags;

typedef struct {
  int w, h;
} Vec2;

typedef struct {
  PlayerMovementFlags movement_flags;
  SDL_Point coordinate;
  Vec2 frame_size;
  int speed;
  TCPsocket *socket;
} Player;

SDL_Rect GetPlayerBoundingBox(Player *player);
void PlayerEvents(SDL_Event *event, Player *player, SDL_Rect *nextPlayerFrame);
void PlayerEventLoop(Player *player);

#endif // !_PLAYER_

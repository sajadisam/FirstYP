#include "player.h"
#include "config.h"
#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <string.h>

SDL_Rect GetPlayerBoundingBox(Player *player) {
  return (SDL_Rect){
      player->coordinate.x,
      player->coordinate.y,
      player->frame_size.w,
      player->frame_size.h,

  };
}

void ConstrainWithinWindow(Player *player) {
  float newPlayerX = player->coordinate.x;
  float newPlayerY = player->coordinate.y;

  if (newPlayerX < 0) {
    newPlayerX = 0;
  } else if (newPlayerX + player->frame_size.w > WINDOW_WIDTH) {
    newPlayerX = WINDOW_WIDTH - player->frame_size.w;
  }
  if (newPlayerY < 0) {
    newPlayerY = 0;
  } else if (newPlayerY + player->frame_size.h > WINDOW_HEIGHT) {
    newPlayerY = WINDOW_HEIGHT - player->frame_size.h;
  }

  player->coordinate.x = newPlayerX;
  player->coordinate.y = newPlayerY;
}

void PlayerEventLoop(Player *player) {
  if (player->movement_flags.up && !player->movement_flags.down)
    player->coordinate.y += -player->speed;
  if (player->movement_flags.down && !player->movement_flags.up)
    player->coordinate.y += player->speed;

  if (player->movement_flags.left && !player->movement_flags.right)
    player->coordinate.x += -player->speed;
  if (player->movement_flags.right && !player->movement_flags.left)
    player->coordinate.x += player->speed;

  ConstrainWithinWindow(player);

  // Send position to server
  if (player->movement_flags.up || player->movement_flags.down ||
      player->movement_flags.right || player->movement_flags.left) {
    char message[1024];
    printf("sending %d %d\n", player->coordinate.x, player->coordinate.y);
    sprintf(message, "PLAYERMOVE %d, %d ", player->coordinate.x,
            player->coordinate.y);
    int len = strlen(message);
    message[len - 1] = '\0';
    if (player->socket != NULL)
      SDLNet_TCP_Send(player->socket, message, len);
  }
}

void PlayerEvents(SDL_Event *event, Player *player, SDL_Rect *nextPlayerFrame) {
  switch (event->type) {
  case SDL_KEYDOWN:
    switch (event->key.keysym.scancode) {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
      player->movement_flags.up = true;
      nextPlayerFrame->y = 3 * player->frame_size.h;
      break;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
      player->movement_flags.left = true;
      nextPlayerFrame->y = 1 * player->frame_size.h;
      break;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
      player->movement_flags.down = true;
      nextPlayerFrame->y = 0 * player->frame_size.h;
      break;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
      player->movement_flags.right = true;
      nextPlayerFrame->y = 2 * player->frame_size.h;
      break;
    }
    break;
  case SDL_KEYUP:
    switch (event->key.keysym.scancode) {
    case SDL_SCANCODE_W:
    case SDL_SCANCODE_UP:
      player->movement_flags.up = false;
      break;
    case SDL_SCANCODE_A:
    case SDL_SCANCODE_LEFT:
      player->movement_flags.left = false;
      break;
    case SDL_SCANCODE_S:
    case SDL_SCANCODE_DOWN:
      player->movement_flags.down = false;
      break;
    case SDL_SCANCODE_D:
    case SDL_SCANCODE_RIGHT:
      player->movement_flags.right = false;
      break;
    }
    break;
  }
}

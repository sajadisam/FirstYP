#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  SDL_Point coordinate;
} Player;

Player *create_player() {
  Player *player = malloc(sizeof(Player));
  player->coordinate.x = 0;
  player->coordinate.y = 0;
  return player;
}

void destroy_player(Player *player) {
  // Check to see if the player is valid
  if (player) {
    free(player);
    player = NULL;
  }
}

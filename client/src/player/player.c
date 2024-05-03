#include "../ui/spritesheet.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  SDL_Point coordinate;
  SpriteSheet *sprite;
} Player;

Player *create_player(SpriteSheet *sprite) {
  Player *player = malloc(sizeof(Player));
  player->coordinate.x = 0;
  player->coordinate.y = 0;
  player->sprite = sprite;
  return player;
}

void destroy_player(Player *player) {
  // Check to see if the player is valid
  if (player) {
    free(player);
    player = NULL;
  }
}

SpriteSheet *get_player_spritesheet(Player *player) { return player->sprite; }

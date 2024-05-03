#include "../ui/spritesheet.h"
#include "player_flags.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  SDL_Point coordinate;
  SpriteSheet *sprite;
  PlayerFlag flags;
  int speed;
} Player;

Player *create_player(SpriteSheet *sprite) {
  Player *player = malloc(sizeof(Player));
  player->coordinate.x = 0;
  player->coordinate.y = 0;
  player->sprite = sprite;
  player->flags = IDLE;
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
PlayerFlag get_player_flags(Player *player) { return player->flags; }
void set_player_flags(Player *player, PlayerFlag flags) {
  player->flags = flags;
}

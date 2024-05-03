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
  player->speed = 2;
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

SDL_Point get_player_coordinates(Player *player) { return player->coordinate; }
void set_player_coordinates(Player *player, SDL_Point coordinate) {
  player->coordinate = coordinate;
}

void player_move_down(Player *player) { player->coordinate.y += player->speed; }
void player_move_up(Player *player) { player->coordinate.y -= player->speed; }
void player_move_right(Player *player) {
  player->coordinate.x += player->speed;
}
void player_move_left(Player *player) { player->coordinate.x -= player->speed; }

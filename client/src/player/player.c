#include "../clock.h"
#include "../ui/spritesheet.h"
#include "player_flags.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  SDL_Point coordinate;
  SpriteSheet *sprite;
  PlayerFlag flags;
  float speed;
} Player;

Player *create_player(SpriteSheet *sprite) {
  Player *player = malloc(sizeof(Player));
  player->coordinate.x = 0;
  player->coordinate.y = 0;
  player->sprite = sprite;
  player->flags = IDLE;
  player->speed = 1.75f;
  return player;
}

void destroy_player(Player *player) {
  if (player) {
    free(player);
    player = NULL;
  }
}

void player_move_down(Player *player) { player->coordinate.y += player->speed; }
void player_move_up(Player *player) { player->coordinate.y -= player->speed; }
void player_move_right(Player *player) {
  player->coordinate.x += player->speed;
}
void player_move_left(Player *player) { player->coordinate.x -= player->speed; }

void perform_movement(Player *player, Timer *animation_speed) {
  SpriteSheet *player_sprite = player->sprite;
  int hFrames = get_spritesheet_h_frames(player->sprite);
  bool clocked = timer_finished(animation_speed);
  int nextH = (get_spritesheet_current_h_frame(player_sprite) + 1) % hFrames;
  if (player->flags & MOVINGDOWN) {
    if (clocked)
      set_spritesheet_current_h_v_frame(player_sprite, nextH, 0);
    player_move_down(player);
  }
  if (player->flags & MOVINGUP) {
    if (clocked)
      set_spritesheet_current_h_v_frame(player_sprite, nextH, 1);
    player_move_up(player);
  }
  if (player->flags & MOVINGRIGHT) {
    if (clocked)
      set_spritesheet_current_h_v_frame(player_sprite, nextH, 2);
    player_move_right(player);
  }
  if (player->flags & MOVINGLEFT) {
    if (clocked)
      set_spritesheet_current_h_v_frame(player_sprite, nextH, 3);
    player_move_left(player);
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

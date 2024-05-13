#include "animation.h"
#include "entity.h"
#include "player_common.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  int id;
  Entity *entity;
  PlayerFlag flags;
  float speed;
  Animation *move_animation;
} Player;

Player *player_create() {
  Player *player = malloc(sizeof(Player));
  player->entity = entity_create();
  player->id = -1;
  entity_move_coord(player->entity, 1500, 1500);
  player->flags = PLAYER_FLAG_NONE;
  player->speed = 2.0f * 60.0f;
  player->move_animation = animation_create(0.075f, 4);
  return player;
}

void player_destroy(Player *player) {
  animation_destroy(player->move_animation);
  entity_destroy(player->entity);
  free(player);
}

void player_update_direction(Player *player) {
  SDL_Point prev = entity_get_prev_coord(player->entity);
  SDL_Point new = entity_get_coord(player->entity);
  int alphaX = prev.x - new.x;
  int alphaY = prev.y - new.y;
  if (alphaY == 0) {
    if (alphaX < 0) // Right
      animation_set_base(player->move_animation, 8);
    else // Left
      animation_set_base(player->move_animation, 12);
  }
  if (alphaX == 0) {
    if (alphaY < 0) // up
      animation_set_base(player->move_animation, 0);
    else // down
      animation_set_base(player->move_animation, 4);
  }
}

void player_update_movement(Player *player, float dt) {
  if (player->flags & PLAYER_FLAG_MOVE_DOWN)
    entity_move_coord(player->entity, 0, player->speed * dt);
  if (player->flags & PLAYER_FLAG_MOVE_UP)
    entity_move_coord(player->entity, 0, -player->speed * dt);
  if (player->flags & PLAYER_FLAG_MOVE_RIGHT)
    entity_move_coord(player->entity, player->speed * dt, 0);
  if (player->flags & PLAYER_FLAG_MOVE_LEFT)
    entity_move_coord(player->entity, -player->speed * dt, 0);
  player_update_direction(player);
}

void player_update(Player *player, float dt) {
  if (player->flags == PLAYER_FLAG_MOVE_HORIZONTAL ||
      player->flags == PLAYER_FLAG_MOVE_VERTICAL ||
      player->flags ==
          (PLAYER_FLAG_MOVE_VERTICAL | PLAYER_FLAG_MOVE_HORIZONTAL)) {
    return;
  }
  player_update_movement(player, dt);
  if ((player->flags & PLAYER_FLAG_MOVE_ANY) == 0) {
    animation_set_frame(player->move_animation, 1);
  } else {
    animation_update(player->move_animation, dt);
  }
}

PlayerFlag get_player_flags(Player *player) { return player->flags; }

void set_player_flags(Player *player, PlayerFlag flags) {
  player->flags = flags;
}

SDL_Point player_get_coord(Player *player) {
  return entity_get_coord(player->entity);
}

int player_get_draw_frame_id(const Player *player) {
  return animation_get_frame(player->move_animation);
}

void player_set_id(Player *player, int id) { player->id = id; }

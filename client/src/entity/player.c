#include "animation.h"
#include "entity.h"
#include "player_common.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
  Entity *entity;
  PlayerFlag flags;
  float speed;
  Animation *move_animation;
} Player;

Player *player_create() {
  Player *player = malloc(sizeof(Player));
  player->entity = entity_create();
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

void player_update_movement(Player *player, float dt) {
  if (player->flags & PLAYER_FLAG_MOVE_DOWN) {
    animation_set_base(player->move_animation, 0);
    entity_move_coord(player->entity, 0, player->speed * dt);
  }
  if (player->flags & PLAYER_FLAG_MOVE_UP) {
    animation_set_base(player->move_animation, 4);
    entity_move_coord(player->entity, 0, -player->speed * dt);
  }
  if (player->flags & PLAYER_FLAG_MOVE_RIGHT) {
    animation_set_base(player->move_animation, 8);
    entity_move_coord(player->entity, player->speed * dt, 0);
  }
  if (player->flags & PLAYER_FLAG_MOVE_LEFT) {
    animation_set_base(player->move_animation, 12);
    entity_move_coord(player->entity, -player->speed * dt, 0);
  }
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

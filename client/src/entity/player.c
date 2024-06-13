#include "../collider/collider.h"
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
  Collider *collider;
  int health;
} Player;

void player_on_collision(Player *playerA, Collider *b) {
  if (collider_get_type(b) == COLLIDER_PLAYER) {
    Player *playerB = (Player *)b;
    // printf("Player %d got collided!\n", playerA->id);
  }
}

Player *player_create() {
  Player *player = malloc(sizeof(Player));
  player->entity = entity_create();
  player->id = -1;
  entity_move_coord(player->entity, 1500, 1500);
  player->flags = PLAYER_FLAG_NONE;
  player->speed = 2.0f * 60.0f;
  player->move_animation = animation_create(0.075f, 3);
  player->health = 100;

  SDL_Point coordinate = entity_get_coord(player->entity);
  player->collider = collider_create(
      (SDL_Rect){
          .x = coordinate.x, .y = coordinate.y, .w = 64 / 2, .h = 64 / 2},
      COLLIDER_PLAYER, player, (void (*)(void *, void *))player_on_collision);
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
  int deltaX = prev.x - new.x;
  int deltaY = prev.y - new.y;
  if (deltaY == 0) {
    if (deltaX < 0) // Right
      animation_set_base(player->move_animation, 6);
    else // Left
      animation_set_base(player->move_animation, 3);
  }
  if (deltaX == 0) {
    if (deltaY < 0) // up
      animation_set_base(player->move_animation, 0);
    else // down
      animation_set_base(player->move_animation, 9);
  }
}

PlayerFlag player_get_flags(Player *player) { return player->flags; }

void player_move_on_flags(Player *player, float dt) {
  if (player->flags & PLAYER_FLAG_MOVE_DOWN)
    entity_move_coord(player->entity, 0, player->speed * dt);
  if (player->flags & PLAYER_FLAG_MOVE_UP)
    entity_move_coord(player->entity, 0, -player->speed * dt);
  if (player->flags & PLAYER_FLAG_MOVE_RIGHT)
    entity_move_coord(player->entity, player->speed * dt, 0);
  if (player->flags & PLAYER_FLAG_MOVE_LEFT)
    entity_move_coord(player->entity, -player->speed * dt, 0);
}

void player_update(Player *player, float dt) {
  if (player->flags == PLAYER_FLAG_MOVE_HORIZONTAL ||
      player->flags == PLAYER_FLAG_MOVE_VERTICAL ||
      player->flags ==
          (PLAYER_FLAG_MOVE_VERTICAL | PLAYER_FLAG_MOVE_HORIZONTAL)) {
    return;
  }
  player_update_direction(player);
  if ((player->flags & PLAYER_FLAG_MOVE_ANY) == 0) {
    animation_set_frame(player->move_animation, 1);
  } else {
    animation_update(player->move_animation, dt);
  }

  SDL_Point coordinate = entity_get_coord(player->entity);
  collider_set_coordinate(player->collider, coordinate.x, coordinate.y);
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

Collider *player_get_collider(Player *player) { return player->collider; }

void player_set_id(Player *player, int id) { player->id = id; }

int player_get_id(Player *player) { return player->id; }
void player_set_flags(Player *player, PlayerFlag flags) {
  player->flags = flags;
}

void player_set_coord(Player *player, int x, int y) {
  entity_set_coord(player->entity, (SDL_Point){x, y});
}


void player_decrement_health(Player *player, int amount) {
  player->health -=amount;
}
int player_get_health(const Player *player) {
  return player->health;
}
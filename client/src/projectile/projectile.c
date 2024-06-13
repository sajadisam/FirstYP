#include "../collider/collider.h"
#include "../entity/entity.h"
#include "../entity/player.h"
#include "projectile_common.h"
#include <stdio.h>

typedef struct {
  float speed;
  float damage;
  SDL_FPoint direction;
  ProjectileType type;
  Collider *collider;
  ProjectileDestroyFunc destroy;
  SDL_Point startcoord;
  void *projectile;
} Projectile;

void projectile_on_collision(Projectile *projectile, Collider *collided) {
  if (collider_get_type(collided) == COLLIDER_PLAYER) {
    Player *player = collider_get_target(collided);
    // printf("Projectile has hit player %d!\n", player_get_id(player));
  }
}

Projectile *projectile_create(float speed, float damage,
                              SDL_Point collision_size, SDL_Point coord,
                              void *entity, ProjectileType type,
                              SDL_FPoint direction,
                              ProjectileDestroyFunc destroy) {
  Projectile *projectile = malloc(sizeof(Projectile));
  projectile->startcoord = coord;
  projectile->speed = speed;
  projectile->damage = damage;
  projectile->collider = collider_create(
      (SDL_Rect){coord.x, coord.y, collision_size.x, collision_size.y},
      COLLIDER_PROJECTILE, projectile,
      (void (*)(void *, void *))projectile_on_collision);
  projectile->direction = direction;
  projectile->destroy = destroy;
  projectile->projectile = entity;
  projectile->type = type;
  return projectile;
}

void projectile_destroy(Projectile *projectile) {
  collider_destroy(projectile->collider);
  free(projectile);
}

float projectile_get_speed(Projectile *projectile) { return projectile->speed; }
float projectile_get_damage(Projectile *projectile) {
  return projectile->damage;
}
SDL_FPoint projectile_get_direction(Projectile *projectile) {
  return projectile->direction;
}

void *projectile_get_projectile(Projectile *projectile) {
  return projectile->projectile;
}

ProjectileType projectile_get_type(Projectile *projectile) {
  return projectile->type;
}
Collider *projectile_get_collider(Projectile *projectile) {
  return projectile->collider;
}

SDL_Point projectile_get_start_coordinate(Projectile *projectile) {
  return projectile->startcoord;
}

SDL_Point projectile_get_coord(Projectile *projectile) {
  Entity *entity = collider_get_entity(projectile->collider);
  SDL_Point coord = entity_get_coord(entity);
  return coord;
}

void projectile_set_coord(Projectile *projectile, SDL_Point coord) {
  Entity *entity = collider_get_entity(projectile->collider);
  entity_set_coord(entity, coord);
}

void projectile_update(Projectile *projectile, float dt) {
  Entity *entity = collider_get_entity(projectile->collider);
  SDL_Point coord = entity_get_coord(entity);
  coord.x += projectile->direction.x * projectile->speed * dt;
  coord.y += projectile->direction.y * projectile->speed * dt;
  projectile_set_coord(projectile, coord);
}

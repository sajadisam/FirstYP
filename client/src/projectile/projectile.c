#include "../collider/collider.h"
#include "../entity/entity.h"
#include "projectile_common.h"

typedef struct {
  float speed;
  float damage;
  SDL_Point direction;
  ProjectileType type;
  Collider *collider;
  ProjectileDestroyFunc destroy;
} Projectile;

void projectile_on_collision(Projectile *projectile, Collider *collided) {
  if (collider_get_type(collided) == COLLIDER_PLAYER) {
    printf("Projectile has been hit!\n");
  }
}

Projectile *projectile_create(float speed, float damage,
                              SDL_Point collision_size, void *entity,
                              ProjectileType type, SDL_Point direction,
                              ProjectileDestroyFunc destroy) {
  Projectile *projectile = malloc(sizeof(Projectile));
  projectile->speed = speed;
  projectile->damage = damage;
  SDL_Point coordinate = entity_get_coord(entity);
  projectile->collider =
      collider_create((SDL_Rect){coordinate.x, coordinate.y, collision_size.x,
                                 collision_size.y},
                      COLLIDER_PROJECTILE, entity,
                      (void (*)(void *, void *))projectile_on_collision);
  projectile->destroy = destroy;
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
SDL_Point projectile_get_direction(Projectile *projectile) {
  return projectile->direction;
}
Entity *projectile_get_entity(Projectile *projectile) {
  return collider_get_entity(projectile->collider);
}
ProjectileType projectile_get_type(Projectile *projectile) {
  return projectile->type;
}
Collider *projectile_get_collider(Projectile *projectile) {
  return projectile->collider;
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

#include "../entity/entity.h"
#include "collider_common.h"
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

typedef struct {
  Entity *entity;
  SDL_Point size;
  ColliderType type;
  void *target;
  OnCollisionFunc on_collision;
} Collider;

Collider *collider_create(SDL_Rect rect, ColliderType type, void *entity,
                          OnCollisionFunc on_collision) {
  Collider *collider = malloc(sizeof(Collider));
  collider->entity = entity_create();
  entity_set_coord(collider->entity, (SDL_Point){rect.x, rect.x});
  collider->size.x = rect.w;
  collider->size.y = rect.h;
  collider->type = type;
  collider->target = entity;
  collider->on_collision = on_collision;
  return collider;
}

void collider_destroy(Collider *collider) {
  entity_destroy(collider->entity);
  free(collider);
}

SDL_Point collider_get_size(Collider *collider) { return collider->size; }

void collider_set_size(Collider *collider, int w, int h) {
  collider->size.x = w;
  collider->size.y = h;
}

void collider_set_coordinate(Collider *collider, int x, int y) {
  entity_set_coord(collider->entity, (SDL_Point){x, y});
}

void *collider_get_target(Collider *collider) { return collider->target; }
Entity *collider_get_entity(Collider *collider) { return collider->entity; }
ColliderType collider_get_type(Collider *collider) { return collider->type; }

bool collider_check(Collider *a, Collider *b) {
  SDL_Point coordA = entity_get_coord(a->entity);
  SDL_Rect rectA = (SDL_Rect){coordA.x, coordA.y, a->size.x, a->size.y};
  SDL_Point coordB = entity_get_coord(b->entity);
  SDL_Rect rectB = (SDL_Rect){coordB.x, coordB.y, b->size.x, b->size.y};
  return SDL_HasIntersection(&rectA, &rectB);
}

bool collider_execute(Collider *a, Collider *b) {
  if (collider_check(a, b)) {
    a->on_collision(a->target, b);
    b->on_collision(b->target, a);
    return true;
  }
  return false;
}

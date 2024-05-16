#include "collider_common.h"
#include <SDL2/SDL_rect.h>
#include <stdbool.h>

typedef struct {
  SDL_Rect rect;
  ColliderType type;
  void *entity;
  OnCollisionFunc on_collision;
} Collider;

Collider *collider_create(SDL_Rect rect, ColliderType type, void *entity,
                          OnCollisionFunc on_collision) {
  Collider *collider = malloc(sizeof(Collider));
  collider->rect = rect;
  collider->type = type;
  collider->entity = entity;
  collider->on_collision = on_collision;
  return collider;
}

void collider_destroy(Collider *collider) { free(collider); }

void collider_set_size(Collider *collider, int w, int h) {
  collider->rect = (SDL_Rect){collider->rect.x, collider->rect.y, w, h};
}

void collider_set_coordinate(Collider *collider, int x, int y) {
  collider->rect.x = x;
  collider->rect.y = y;
}

void collider_set_rect(Collider *collider, SDL_Rect rect) {
  collider->rect = rect;
}

void *collider_get_entity(Collider *collider) { return collider->entity; }
ColliderType collider_get_type(Collider *collider) { return collider->type; }
SDL_Rect collider_get_rect(Collider *collider) { return collider->rect; }

bool collider_check(Collider *a, Collider *b) {
  return SDL_HasIntersection(&a->rect, &b->rect);
}

void collider_execute(Collider *a, Collider *b) {
  if (collider_check(a, b)) {
    a->on_collision(a->entity, b);
    b->on_collision(b->entity, a);
  }
}

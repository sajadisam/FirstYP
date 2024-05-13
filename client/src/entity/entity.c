#include <SDL2/SDL_rect.h>

typedef struct {
  SDL_Point prevCoordinate;
  SDL_Point coordinate;
} Entity;

Entity *entity_create() {
  Entity *entity = malloc(sizeof(Entity));
  entity->prevCoordinate.x = 0;
  entity->prevCoordinate.y = 0;
  entity->coordinate.x = 0;
  entity->coordinate.y = 0;
  return entity;
}

void entity_destroy(Entity *entity) { free(entity); }

SDL_Point entity_get_prev_coord(const Entity *entity) {
  return entity->prevCoordinate;
}
SDL_Point entity_get_coord(const Entity *entity) { return entity->coordinate; }

void entity_set_coord(Entity *entity, SDL_Point point) {
  entity->prevCoordinate = entity->coordinate;
  entity->coordinate = point;
}

void entity_move_coord(Entity *entity, float dx, float dy) {
  entity->prevCoordinate = entity->coordinate;
  entity->coordinate.x += (int)dx;
  entity->coordinate.y += (int)dy;
}

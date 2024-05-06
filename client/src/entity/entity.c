#include <SDL2/SDL_rect.h>

typedef struct {
  SDL_Point coordinate;
} Entity;

Entity *entity_create() {
  Entity *entity = malloc(sizeof(Entity));
  entity->coordinate.x = 0;
  entity->coordinate.y = 0;
  return entity;
}

void entity_destroy(Entity *entity) { free(entity); }

SDL_Point entity_get_coord(Entity const *entity) { return entity->coordinate; }

void entity_set_coord(Entity *entity, SDL_Point point) {
  entity->coordinate = point;
}

void entity_move_coord(Entity *entity, float dx, float dy) {
  entity->coordinate.x += (int)dx;
  entity->coordinate.y += (int)dy;
}

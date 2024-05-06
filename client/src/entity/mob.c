#include "entity.h"
#include <SDL2/SDL_rect.h>
#include <malloc.h>

typedef struct {
  Entity *entity;
} Mob;

Mob *mob_create() {
  Mob *mob = malloc(sizeof(Mob));
  mob->entity = entity_create();
  return mob;
}

void mob_destroy(Mob *mob) {
  entity_destroy(mob->entity);
  free(mob);
}

SDL_Point mob_get_coord(Mob *mob) { return entity_get_coord(mob->entity); }

void mob_set_coord(Mob *mob, SDL_Point coord) {
  entity_set_coord(mob->entity, coord);
}

int mob_get_draw_frame_id(Mob const *player) { return 1; }

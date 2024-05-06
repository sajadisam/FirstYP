#ifndef MOB_H
#define MOB_H

#include "entity.h"
#include <SDL2/SDL_rect.h>

typedef struct Mob Mob;

Mob *mob_create();
void mob_destroy(Mob *mob);

SDL_Point mob_get_coord(Mob *mob);
void mob_set_coord(Mob *mob, SDL_Point coord);
int mob_get_draw_frame_id(Mob const *player);

#endif // MOB_H

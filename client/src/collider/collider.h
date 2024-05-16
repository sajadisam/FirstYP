#ifndef _COLLIDER_
#define _COLLIDER_

#include "../entity/entity.h"
#include "collider_common.h"
#include <SDL2/SDL_rect.h>
#include <stdbool.h>
typedef struct Collider Collider;

Collider *collider_create(SDL_Rect rect, ColliderType type, void *entity,
                          OnCollisionFunc on_collision);
void collider_destroy(Collider *collider);
int collider_check(Collider *a, Collider *b);
void collider_set_size(Collider *collider, int w, int h);
void collider_set_coordinate(Collider *collider, int x, int y);
void collider_set_rect(Collider *collider, SDL_Rect rect);
void *collider_get_target(Collider *collider);
Entity *collider_get_entity(Collider *collider);
ColliderType collider_get_type(Collider *collider);
bool collider_execute(Collider *a, Collider *b);
SDL_Point collider_get_size(Collider *collider);

#endif // !_COLLIDER_

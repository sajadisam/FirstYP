#ifndef _TOMATO_
#define _TOMATO_

#include "projectile.h"
#include <SDL2/SDL_rect.h>
typedef struct TomatoProjectile TomatoProjectile;

TomatoProjectile *tomatoprojectile_create(SDL_Point direction, SDL_Point coord);
void tomatoprojectile_destroy(TomatoProjectile *tomato);
Projectile *tomatoprojectile_get_projectile(TomatoProjectile *tomato);

#endif // !_TOMATO_

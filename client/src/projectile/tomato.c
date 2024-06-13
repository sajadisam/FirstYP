#include "projectile.h"

typedef struct {
  Projectile *projectile;
} TomatoProjectile;

void tomatoprojectile_destroy(TomatoProjectile *tomato) {
  projectile_destroy(tomato->projectile);
  free(tomato);
}

TomatoProjectile *tomatoprojectile_create(SDL_FPoint direction,
                                          SDL_Point coord) {
  TomatoProjectile *tomato = malloc(sizeof(TomatoProjectile));
  SDL_Point size = (SDL_Point){.x = 32, .y = 32};
  tomato->projectile =
      projectile_create(150.0f, 10.0f, size, tomato, PROJECTILE_TOMATO,
                        direction, (void (*)(void *))tomatoprojectile_destroy);
  projectile_set_coord(tomato->projectile, coord);
  return tomato;
}

Projectile *tomatoprojectile_get_projectile(TomatoProjectile *tomato) {
  return tomato->projectile;
}

#ifndef HEALTH_H
#define HEALTH_H

#include <SDL2/SDL.h>

typedef struct HealthBar HealthBar;

HealthBar *health_bar_create(SDL_Renderer *renderer);
void health_bar_destroy(HealthBar *health_bar);
void health_bar_update(HealthBar *health_bar, int health);
void health_bar_draw(HealthBar *health_bar, SDL_Renderer *renderer);

#endif // HEALTH_H

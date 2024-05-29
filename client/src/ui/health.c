#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect rect;
    int health;
} HealthBar;

HealthBar *health_bar_create(SDL_Renderer *renderer) {
    HealthBar *health_bar = (HealthBar *)malloc(sizeof(HealthBar));
    health_bar->rect = (SDL_Rect){20, 20, 300, 30};
    health_bar->health = 100;
    return health_bar;
}

void health_bar_destroy(HealthBar *health_bar) {
    free(health_bar);
}
void health_bar_update(HealthBar *health_bar, int health) {
    health_bar->health = health;
    health_bar->rect.w = (300 * health) / 100;
}

void health_bar_draw(HealthBar *health_bar, SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect background_rect = {health_bar->rect.x, health_bar->rect.y, 300, health_bar->rect.h};
    SDL_RenderFillRect(renderer, &background_rect);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &health_bar->rect);
}

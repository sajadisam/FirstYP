#ifndef WORLD_RENDERER_H
#define WORLD_RENDERER_H

#include <SDL2/SDL_render.h>

typedef struct WorldRenderer WorldRenderer;

WorldRenderer *world_renderer_create(SDL_Renderer *renderer);

void world_renderer_destroy(WorldRenderer *world_renderer);
void world_renderer_render(WorldRenderer *renderer, void *world,
                           SDL_Point pivot);

SDL_Renderer *world_renderer_get_renderer(WorldRenderer *world_renderer);

#endif // WORLD_RENDERER_H

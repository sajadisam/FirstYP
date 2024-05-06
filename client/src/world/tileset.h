#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL_render.h>

typedef struct Tileset Tileset;

Tileset *tileset_create(SDL_Renderer *renderer, const char *path, int cellWidth,
                        int cellHeight);

void tileset_destroy(Tileset *tileset);

void tileset_draw_tile(Tileset *tileset, SDL_Renderer *renderer, int tile,
                       SDL_Rect *dst);

#endif // TILE_H

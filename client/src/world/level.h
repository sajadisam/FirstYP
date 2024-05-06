#ifndef LEVEL_H
#define LEVEL_H

#include "level_common.h"
#include "tileset.h"
#include <SDL2/SDL_render.h>

typedef struct Level Level;

Level *level_create(SDL_Renderer *renderer, char const *tilesetPath,
                    char const *levelPath);

void level_destroy(Level *level);

int level_get_tile(Level const *level, unsigned int x, unsigned int y);
unsigned int level_get_width(Level const *level);
unsigned int level_get_height(Level const *level);
Tileset *level_get_tileset(Level *level);

#endif // LEVEL_H

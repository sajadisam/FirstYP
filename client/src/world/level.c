#include "level_common.h"
#include "tileset.h"

#include <SDL2/SDL_image.h>
#include <assert.h>
#include <ctype.h>
#include <malloc.h>
#include <stdio.h>

#define WORLD_MAX_WIDTH (256)
#define WORLD_MAX_HEIGHT (256)
#define WORLD_MAX_TILE_COUNT (WORLD_MAX_WIDTH * WORLD_MAX_HEIGHT)

typedef struct {
  Tileset *tileset;
  int *tiles;
  unsigned int width;
  unsigned int height;
} Level;

void level_load_tiles(char const *levelPath, int **pTiles, int *pWidth,
                      int *pHeight) {
  FILE *file = fopen(levelPath, "r");

  int maxWidth = 0;
  int height = 0;
  int *tempTiles = malloc(sizeof(int) * WORLD_MAX_TILE_COUNT);

  char lineBuffer[1024];
  while (feof(file) == 0) {
    fgets(lineBuffer, 1024, file);
    char *linePtr = lineBuffer;
    int width = 0;
    while (*linePtr) {
      int tile = 0;
      while (isdigit(*linePtr)) {
        tile = tile * 10 + (*linePtr - '0');
        linePtr++;
      }
      tempTiles[height * WORLD_MAX_WIDTH + width] = tile;
      width++;
      if (!*linePtr) {
        break;
      } else if (*linePtr == '\r' || *linePtr == '\n') {
        linePtr++;
        if (*linePtr == '\n') {
          linePtr++;
        }
        break;
      } else if (*linePtr == ',') {
        linePtr++;
      } else {
        assert(0);
      }
    }
    if (width > maxWidth) {
      maxWidth = width;
    }
    height++;
  }
  fclose(file);

  int *tiles = malloc(maxWidth * height * sizeof(int));
  for (unsigned int y = 0; y < height; y++) {
    for (unsigned int x = 0; x < maxWidth; x++) {
      tiles[y * maxWidth + x] = tempTiles[y * WORLD_MAX_WIDTH + x];
    }
  }
  free(tempTiles);

  *pTiles = tiles;
  *pWidth = maxWidth;
  *pHeight = height;
}

Level *level_create(SDL_Renderer *renderer, const char *tilesetPath,
                    const char *levelPath) {
  Tileset *tileset = tileset_create(renderer, tilesetPath, 16, 16);

  int width, height;
  int *tiles;
  level_load_tiles(levelPath, &tiles, &width, &height);

  Level *level = malloc(sizeof(Level));
  level->tileset = tileset;
  level->tiles = tiles;
  level->width = width;
  level->height = height;
  return level;
}

void level_destroy(Level *level) {
  tileset_destroy(level->tileset);
  free(level->tiles);
  free(level);
}

void level_draw_tile(SDL_Renderer *renderer, const Level *level, int x, int y,
                     unsigned int tile) {
  SDL_Rect dst = {.x = x * LEVEL_TILE_SIZE,
                  .y = y * LEVEL_TILE_SIZE,
                  .w = LEVEL_TILE_SIZE,
                  .h = LEVEL_TILE_SIZE};
  tileset_draw_tile(level->tileset, renderer, tile, &dst);
}

int level_get_tile(const Level *level, unsigned int x, unsigned int y) {
  return level->tiles[y * level->width + x];
}

unsigned int level_get_width(const Level *level) { return level->width; }

unsigned int level_get_height(const Level *level) { return level->height; }

Tileset *level_get_tileset(Level *level) { return level->tileset; }

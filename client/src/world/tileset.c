#include "../ui/spritesheet.h"

typedef struct {
  SpriteSheet *geometry_sheet;
} Tileset;

Tileset *tileset_create(SDL_Renderer *renderer, char const *path, int cellWidth,
                        int cellHeight) {
  SpriteSheet *geometry_sheet =
      spritesheet_create(renderer, path, cellWidth, cellHeight);
  Tileset *tileset = malloc(sizeof(Tileset));
  tileset->geometry_sheet = geometry_sheet;
  return tileset;
}

void tileset_destroy(Tileset *tileset) {
  spritesheet_destroy(tileset->geometry_sheet);
  free(tileset);
}

void tileset_draw_tile(Tileset *tileset, SDL_Renderer *renderer, int tile,
                       SDL_Rect *dst) {
  int cellX = tile % spritesheet_get_width(tileset->geometry_sheet);
  int cellY = tile / spritesheet_get_width(tileset->geometry_sheet);
  spritesheet_draw(renderer, tileset->geometry_sheet, cellX, cellY, dst);
}

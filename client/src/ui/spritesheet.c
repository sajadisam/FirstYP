#include "sprite.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <assert.h>

typedef struct {
  int cellWidth;
  int cellHeight;
  int width;
  int height;
  Sprite *sprite;
} SpriteSheet;

SpriteSheet *spritesheet_create(SDL_Renderer *renderer, const char *path,
                                int cellWidth, int cellHeight) {
  SpriteSheet *sheet = malloc(sizeof(SpriteSheet));
  sheet->sprite = sprite_create(renderer, path);
  assert(sprite_get_width(sheet->sprite) % cellWidth == 0);
  assert(sprite_get_height(sheet->sprite) % cellHeight == 0);
  sheet->cellWidth = cellWidth;
  sheet->cellHeight = cellHeight;
  sheet->width = sprite_get_width(sheet->sprite) / cellWidth;
  sheet->height = sprite_get_height(sheet->sprite) / cellHeight;
  return sheet;
}

void spritesheet_destroy(SpriteSheet *sheet) {
  if (sheet->sprite) {
    sprite_destroy(sheet->sprite);
    sheet->sprite = NULL;
  }
  free(sheet);
}

void spritesheet_draw(SDL_Renderer *renderer, SpriteSheet *sheet, int cellX,
                      int cellY, SDL_Rect *dst) {
  SDL_Rect src = {.x = cellX * sheet->cellWidth,
                  .y = cellY * sheet->cellHeight,
                  .w = sheet->cellWidth,
                  .h = sheet->cellHeight};
  sprite_draw(renderer, sheet->sprite, &src, dst);
}

int spritesheet_get_width(SpriteSheet *sheet) { return sheet->width; }
int spritesheet_get_height(SpriteSheet *sheet) { return sheet->height; }
int spritesheet_get_cellwidth(SpriteSheet *sheet) { return sheet->cellWidth; }
int spritesheet_get_cellheight(SpriteSheet *sheet) { return sheet->cellHeight; }

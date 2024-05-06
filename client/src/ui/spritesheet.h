#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SDL2/SDL_render.h>

typedef struct SpriteSheet SpriteSheet;

SpriteSheet *spritesheet_create(SDL_Renderer *renderer, const char *path,
                                int cellWidth, int cellHeight);
void spritesheet_destroy(SpriteSheet *sheet);

void spritesheet_draw(SDL_Renderer *renderer, SpriteSheet *sheet, int cellX,
                      int cellY, SDL_Rect *dst);

int spritesheet_get_width(SpriteSheet *sheet);
int spritesheet_get_height(SpriteSheet *sheet);

#endif // SPRITESHEET_H

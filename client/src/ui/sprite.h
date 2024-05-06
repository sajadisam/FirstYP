#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL_render.h>

typedef struct Sprite Sprite;

Sprite *sprite_create(SDL_Renderer *renderer, char const *path);
void sprite_destroy(Sprite *sprite);

void sprite_draw(SDL_Renderer *renderer, Sprite *sprite, SDL_Rect *src,
                 SDL_Rect *dst);

int sprite_get_width(Sprite *sprite);
int sprite_get_height(Sprite *sprite);

#endif // SPRITE_H

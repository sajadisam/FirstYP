#ifndef _SPRITE_
#define _SPRITE_

#include "../game.h"
#include "../window/window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

typedef struct sprite Sprite;

/* GETTERS & SETTERS */
SDL_Texture *get_sprite_texture(Sprite *sprite);
SDL_Rect get_sprite_size(Sprite *sprite);

/*
 * Create a sprite from a path
 */
Sprite *create_sprite(Window *window, const char *path, SDL_Point coordinate);

void render_sprite_loop(Game *game, Sprite *sprite);

/*
 * Destroy a created sprite
 */
void destroy_sprite(Sprite *sprite);

#endif

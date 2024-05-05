#ifndef _SPRITE_
#define _SPRITE_

#include "../math/size.h"
#include "../window/window.h"
#include "sprite_render_options.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

typedef struct sprite Sprite;

/*
 * Create a sprite from a path. Use set_sprite_render_options() to prepare for
 * rendering
 */
Sprite *create_sprite(const Window *window, const char *path);

/*
 * Destroy a created sprite
 */
void destroy_sprite(Sprite *sprite);

/*
 * Sets the render options of the sprite
 */

SDL_Texture *get_sprite_texture(Sprite *sprite);
SpriteRenderOptions get_sprite_render_options(Sprite *sprite);
SDL_Rect get_sprite_size(Sprite *sprite);

void set_sprite_render_crop(Sprite *sprite, SDL_Point crop);
void set_sprite_render_clip(Sprite *sprite, Size clip);
void set_sprite_render_coordinate(Sprite *sprite, SDL_Point coordinate);
void set_sprite_render_size(Sprite *sprite, Size size);

#endif

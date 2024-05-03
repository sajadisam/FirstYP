#ifndef _SPRITE_
#define _SPRITE_

#include "../math/size.h"
#include "../window/window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

typedef struct sprite Sprite;

/*
 * Create a sprite from a path
 */
Sprite *create_sprite(const Window *window, const char *path);

/*
 * Destroy a created sprite
 */
void destroy_sprite(Sprite *sprite);

/*
 * Renders a sprite into the screen
 */
void render_sprite(struct Game *game, const Sprite *sprite, const Size size,
                   const SDL_Point coordinate);

/*
 * Renders all sprites in game
 */
void render_sprite_loop(struct Game *game, Sprite *sprite);

SDL_Texture *get_sprite_texture(Sprite *sprite);
SDL_Rect get_sprite_size(Sprite *sprite);

#endif

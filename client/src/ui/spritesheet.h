#ifndef _SPRITESHEET_
#define _SPRITESHEET_

// #include "../game.h"
typedef struct game Game;

#include "../math/size.h"
#include "../window/window.h"

// Composes a sprite to be animatable
typedef struct spriteSheet SpriteSheet;

/*
 * Sets the current frame to be rendered
 * @arg sprite: Sprite to set the current frame of
 * @arg frame: frame index going clockwise
 */
void set_current_frame(SpriteSheet *sprite, int frame);

/*
 * Create an spritesheet based on vertical and horizontal frames
 */
SpriteSheet *create_spritesheet(Window *window, const char *path, int hFrames,
                                int vFrames);

/*
 * Renders the sprite from the sprite sheet based on the current frame set by
 * set_current_frame()
 */
void render_spritesheet(Game *game, SpriteSheet *sprite, Size size,
                        SDL_Point coordinate);

#endif // !_SPRITESHEET_

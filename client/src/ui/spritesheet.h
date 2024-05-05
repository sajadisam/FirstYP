#ifndef _SPRITESHEET_
#define _SPRITESHEET_

#include "../math/size.h"
#include "../window/window.h"

// Composes a sprite to be animatable
typedef struct spriteSheet SpriteSheet;
typedef struct game Game;

/*
 * Create an spritesheet based on vertical and horizontal frames
 */
SpriteSheet *create_spritesheet(const Window *window, const char *path,
                                const int hFrames, const int vFrames);

/*
 * Sets the render options of the spritesheet, similar to sprite spreadsheet but
 * with extra functionality. Also depends on set_current_frame()
 */
void set_spritesheet_render_options(SpriteSheet *sprite, const Size size,
                                    const SDL_Point coordinate);

/*
 * Gets the clockwise index of the spridesheet
 */
int get_current_frame(SpriteSheet *sprite);

struct Sprite *get_spritesheet_sprite(const SpriteSheet *sprite);
int get_spritesheet_h_frames(const SpriteSheet *sprite);
int get_spritesheet_v_frames(const SpriteSheet *sprite);
void set_spritesheet_current_h_v_frame(SpriteSheet *sprite, const int h,
                                       const int v);
int get_spritesheet_current_h_frame(const SpriteSheet *sprite);
int get_spritesheet_current_v_frame(const SpriteSheet *sprite);
void set_spritesheet_current_h_frame(SpriteSheet *sprite, const int frame);
void set_spritesheet_current_v_frame(SpriteSheet *sprite, const int frame);

#endif // !_SPRITESHEET_

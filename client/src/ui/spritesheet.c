#include "../game.h"
#include "../window/window.h"
#include "sprite.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

typedef struct {
  int currentHFrame;
  int currentVFrame;
  int hFrames;
  int vFrames;
  Sprite *sprite;
} SpriteSheet;

SpriteSheet *create_spritesheet(const Window *window, const char *path,
                                const int hFrames, const int vFrames) {
  SpriteSheet *sprite = malloc(sizeof(SpriteSheet));
  sprite->sprite = create_sprite(window, path);
  sprite->hFrames = hFrames;
  sprite->vFrames = vFrames;
  sprite->currentHFrame = 0;
  sprite->currentVFrame = 0;
  return sprite;
}
void set_spritesheet_render_options(SpriteSheet *sprite, const Size size,
                                    const SDL_Point coordinate) {
  SDL_Rect spriteSize = get_sprite_size(sprite->sprite);
  SDL_Texture *texture = get_sprite_texture(sprite->sprite);
  int horizontal = spriteSize.w / sprite->hFrames;
  int vertical = spriteSize.h / sprite->vFrames;

  set_sprite_render_coordinate(sprite->sprite, coordinate);
  set_sprite_render_clip(sprite->sprite,
                         (Size){horizontal * sprite->currentHFrame,
                                vertical * sprite->currentVFrame});
  set_sprite_render_size(sprite->sprite, size);
  set_sprite_render_crop(sprite->sprite, (SDL_Point){horizontal, vertical});
}

Sprite *get_spritesheet_sprite(const SpriteSheet *sprite) {
  return sprite->sprite;
}
int get_spritesheet_h_frames(const SpriteSheet *sprite) {
  return sprite->hFrames;
}
int get_spritesheet_v_frames(const SpriteSheet *sprite) {
  return sprite->vFrames;
}
int get_spritesheet_current_h_frame(const SpriteSheet *sprite) {
  return sprite->currentHFrame;
}
int get_spritesheet_current_v_frame(const SpriteSheet *sprite) {
  return sprite->currentVFrame;
}
void set_spritesheet_current_h_frame(SpriteSheet *sprite, const int frame) {
  sprite->currentHFrame = frame;
}
void set_spritesheet_current_h_v_frame(SpriteSheet *sprite, const int h,
                                       const int v) {
  sprite->currentHFrame = h;
  sprite->currentVFrame = v;
}
void set_spritesheet_current_v_frame(SpriteSheet *sprite, const int frame) {
  sprite->currentVFrame = frame;
}

int get_current_frame(SpriteSheet *sprite) {
  return sprite->currentHFrame + (sprite->currentVFrame * sprite->hFrames);
}

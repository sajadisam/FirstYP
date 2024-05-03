#include "../game.h"
#include "../shared/debug.h"
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

SpriteSheet *create_spritesheet(Window *window, const char *path, int hFrames,
                                int vFrames) {
  SpriteSheet *sprite = malloc(sizeof(SpriteSheet));
  sprite->sprite = create_sprite(window, path);
  sprite->hFrames = hFrames;
  sprite->vFrames = vFrames;
  sprite->currentHFrame = 0;
  sprite->currentVFrame = 0;
  return sprite;
}

int get_spritesheet_current_h_frame(SpriteSheet *sprite) {
  return sprite->currentHFrame;
}
int get_spritesheet_current_v_frame(SpriteSheet *sprite) {
  return sprite->currentVFrame;
}
void set_spritesheet_current_h_frame(SpriteSheet *sprite, int frame) {
  sprite->currentHFrame = frame;
}
void set_spritesheet_current_v_frame(SpriteSheet *sprite, int frame) {
  sprite->currentVFrame = frame;
}
void set_current_frame(SpriteSheet *sprite, int frame) {
  sprite->currentHFrame = ceil(sprite->hFrames / frame);
}

void render_spritesheet(Game *game, SpriteSheet *sprite, Size size,
                        SDL_Point coordinate) {
  SDL_Rect spriteSize = get_sprite_size(sprite->sprite);
  SDL_Texture *texture = get_sprite_texture(sprite->sprite);
  SDL_Renderer *renderer = get_game_renderer(game);
  int horizontal = spriteSize.w / sprite->hFrames;
  int vertical = spriteSize.h / sprite->vFrames;
  SDL_RenderCopy(renderer, texture,
                 &(SDL_Rect){horizontal * sprite->currentHFrame,
                             vertical * sprite->currentVFrame, horizontal,
                             vertical},
                 &(SDL_Rect){coordinate.x, coordinate.y, horizontal + size.w,
                             vertical + size.h});
}

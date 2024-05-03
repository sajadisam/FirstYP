#include "sprite.h"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdlib.h>

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

void set_current_frame(SpriteSheet *sprite, int frame) {
  // sprite->horizontalFrames = ceil(sprite->horizontalFrames / frame);
  // sprite->verticalFrames = frame;
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

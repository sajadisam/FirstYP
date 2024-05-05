#include "../math/size.h"
#include "../shared/misc.h"
#include "../window/window.h"
#include "sprite_render_options.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

typedef struct {
  SDL_Rect size;
  SDL_Texture *texture;
  SpriteRenderOptions render;
} Sprite;

Sprite *create_sprite(const Window *window, const char *path) {
  SDL_Surface *pSurface = IMG_Load(path);
  if (!pSurface)
    on_sdl_error();

  SDL_Texture *texture =
      SDL_CreateTextureFromSurface(get_window_renderer(window), pSurface);
  SDL_FreeSurface(pSurface);
  if (!texture)
    on_sdl_error();

  int width, height;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);

  Sprite *sprite = malloc(sizeof(Sprite));
  sprite->texture = texture;
  sprite->size.w = width;
  sprite->size.h = height;
  sprite->size.x = 0;
  sprite->size.y = 0;
  sprite->render = (SpriteRenderOptions){.coordinate = (SDL_Point){0, 0},
                                         .size = (Size){width, height},
                                         .clip = (Size){0, 0},
                                         .crop = (SDL_Point){-1, -1}};
  return sprite;
}

void destroy_sprite(Sprite *sprite) {
  if (sprite && sprite->texture) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
    sprite = NULL;
  }
}

void set_sprite_render_crop(Sprite *sprite, SDL_Point crop) {
  sprite->render.crop = crop;
}
void set_sprite_render_clip(Sprite *sprite, Size clip) {
  sprite->render.clip = clip;
}
void set_sprite_render_coordinate(Sprite *sprite, SDL_Point coordinate) {
  sprite->render.coordinate = coordinate;
}
void set_sprite_render_size(Sprite *sprite, Size size) {
  sprite->render.size = size;
}

SpriteRenderOptions get_sprite_render_options(Sprite *sprite) {
  return sprite->render;
}
SDL_Texture *get_sprite_texture(Sprite *sprite) { return sprite->texture; }
SDL_Rect get_sprite_size(Sprite *sprite) { return sprite->size; }

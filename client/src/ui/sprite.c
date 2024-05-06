#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <assert.h>
#include <stdio.h>

typedef struct {
  SDL_Texture *texture;
  SDL_Rect size;
} Sprite;

Sprite *sprite_create(SDL_Renderer *renderer, const char *path) {
  SDL_Surface *surface = IMG_Load(path);
  assert(surface);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  int width, height;
  SDL_QueryTexture(texture, NULL, NULL, &width, &height);

  Sprite *sprite = malloc(sizeof(Sprite));
  sprite->texture = texture;
  sprite->size.w = width;
  sprite->size.h = height;
  sprite->size.x = 0;
  sprite->size.y = 0;
  return sprite;
}

void sprite_destroy(Sprite *sprite) {
  if (sprite->texture) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
  }
  free(sprite);
}

void sprite_draw(SDL_Renderer *renderer, Sprite *sprite, SDL_Rect *src,
                 SDL_Rect *dst) {
  SDL_RenderCopy(renderer, sprite->texture, src, dst);
}

int sprite_get_width(Sprite *sprite) { return sprite->size.w; }

int sprite_get_height(Sprite *sprite) { return sprite->size.h; }

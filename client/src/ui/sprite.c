#include "../game.h"
#include "../math/size.h"
#include "../shared/misc.h"
#include "../window/window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

typedef struct {
  SDL_Rect size;
  SDL_Texture *texture;
} Sprite;

/* GETTERS & SETTERS */
SDL_Texture *get_sprite_texture(Sprite *sprite) { return sprite->texture; }
SDL_Rect get_sprite_size(Sprite *sprite) { return sprite->size; }

Sprite *create_sprite(Window *window, const char *path) {
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
  return sprite;
}

void destroy_sprite(Sprite *sprite) {
  if (sprite && sprite->texture) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
    sprite = NULL;
  }
}

void render_sprite(Game *game, Sprite *sprite, Size size,
                   SDL_Point coordinate) {
  // SDL_RenderCopy(get_game_renderer(game), get_sprite_texture(sprite), NULL,
  //                &(SDL_Rect){coordinate.x, coordinate.y,
  //                            sprite->size.w + size.w, sprite->size.h +
  //                            size.h});
  SDL_RenderCopy(get_game_renderer(game), get_sprite_texture(sprite), NULL,
                 NULL);
}

// TODO(Xelian): Change to use an array of sprites
void render_sprite_loop(Game *game, Sprite *sprite) {
  SDL_RenderClear(get_game_renderer(game));
  render_sprite(game, sprite, (Size){20, 20}, (SDL_Point){20, 20});
  SDL_RenderPresent(get_game_renderer(game));
}

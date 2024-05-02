#include "../game.h"
#include "../math/size.h"
#include "../shared/misc.h"
#include "../window/window.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

typedef struct {
  // TODO(xelian): Change later to Size
  SDL_Rect size;
  SDL_Texture *texture;
} Sprite;

/* GETTERS & SETTERS */
SDL_Texture *get_sprite_texture(Sprite *sprite) { return sprite->texture; }
SDL_Rect get_sprite_size(Sprite *sprite) { return sprite->size; }

Sprite *create_sprite(Window *window, const char *path, SDL_Point coordinate) {
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
  sprite->size.h = width;
  sprite->size.x = coordinate.x;
  sprite->size.y = coordinate.y;
  return sprite;
}

void destroy_sprite(Sprite *sprite) {
  if (sprite && sprite->texture) {
    SDL_DestroyTexture(sprite->texture);
    sprite->texture = NULL;
    sprite = NULL;
  }
}

// TODO(Xelian): Change to use an array of sprites
void render_sprite_loop(Game *game, Sprite *sprite) {
  SDL_RenderClear(get_game_renderer(game));
  SDL_RenderCopy(get_game_renderer(game), get_sprite_texture(sprite), NULL,
                 NULL);
  SDL_RenderPresent(get_game_renderer(game));
}

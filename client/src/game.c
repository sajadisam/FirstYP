#include "clock.h"
#include "player/player.h"
#include "shared/debug.h"
#include "ui/sprite.h"
#include "window/window.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Window *window;
  Player *player;
  Clock *clock;
  Sprite **sprites;
  int sprites_len;
} Game;

Game *create_game(Window *window, Player *player, Clock *clock) {
  Game *game = malloc(sizeof(Game));
  game->window = window;
  game->player = player;
  game->clock = clock;
  game->sprites = malloc(sizeof(Sprite *));
  game->sprites_len = 0;
  return game;
}

Sprite *add_game_sprite(Game *game, Sprite *sprite) {
  game->sprites =
      realloc(game->sprites, sizeof(Sprite *) * (game->sprites_len + 1));
  game->sprites[game->sprites_len++] = sprite;
  return sprite;
}

Sprite *create_game_sprite(Game *game, const char *path) {
  return add_game_sprite(game, create_sprite(game->window, path));
}

void render_game_sprites(Game *game) {
  SDL_Renderer *renderer = get_window_renderer(game->window);
  SDL_RenderClear(renderer);
  for (int i = 0; i < game->sprites_len; i++) {

    Sprite *sprite = game->sprites[i];
    SDL_Texture *texture = get_sprite_texture(sprite);
    SpriteRenderOptions options = get_sprite_render_options(sprite);
    SDL_Rect spriteSize = get_sprite_size(sprite);
    int cropW = options.crop.x != -1 ? options.crop.x : spriteSize.w;
    int cropH = options.crop.y != -1 ? options.crop.y : spriteSize.h;

    SDL_RenderCopy(renderer, texture,
                   &(SDL_Rect){options.clip.w, options.clip.h, cropW, cropH},
                   &(SDL_Rect){options.coordinate.x, options.coordinate.y,
                               options.size.w, options.size.h});
  }
  SDL_RenderPresent(renderer);
}

SDL_Renderer *get_game_renderer(const Game *game) {
  return get_window_renderer(game->window);
}
Window *get_game_window(const Game *game) { return game->window; }
Player *get_game_player(const Game *game) { return game->player; }
Clock *get_game_clock(const Game *game) { return game->clock; }

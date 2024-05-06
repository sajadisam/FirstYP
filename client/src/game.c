#include "entity/mob.h"
#include "entity/player.h"
#include "window/window.h"
#include "world/world.h"
#include <SDL2/SDL_timer.h>
#include <stdlib.h>

typedef struct {
  Window *window;
  World *world;
  int selfPlayerId;
} Game;

Player *game_get_self_player(Game *game) {
  return world_get_player(game->world, game->selfPlayerId);
}

Window *get_game_window(const Game *game) { return game->window; }

int window_event_callback(SDL_Event const *event, void *arg) {
  Game *game = arg;
  if (event->type == SDL_QUIT) {
    return 1;
  }
  Player *player = game_get_self_player(game);
  PlayerFlag flags = get_player_flags(player);
  switch (event->type) {
  case SDL_MOUSEMOTION:
    set_window_mouse_coordinate(get_game_window(game),
                                (SDL_Point){event->motion.x, event->motion.y});
    break;
  case SDL_KEYDOWN: {
    SDL_Scancode code = event->key.keysym.scancode;
    if (code == SDL_SCANCODE_UP || code == SDL_SCANCODE_W)
      flags |= PLAYER_FLAG_MOVE_UP;
    if (code == SDL_SCANCODE_DOWN || code == SDL_SCANCODE_S)
      flags |= PLAYER_FLAG_MOVE_DOWN;
    if (code == SDL_SCANCODE_RIGHT || code == SDL_SCANCODE_D)
      flags |= PLAYER_FLAG_MOVE_RIGHT;
    if (code == SDL_SCANCODE_LEFT || code == SDL_SCANCODE_A)
      flags |= PLAYER_FLAG_MOVE_LEFT;
  } break;
  case SDL_KEYUP: {
    SDL_Scancode code = event->key.keysym.scancode;
    if (code == SDL_SCANCODE_UP || code == SDL_SCANCODE_W)
      flags &= ~PLAYER_FLAG_MOVE_UP;
    if (code == SDL_SCANCODE_DOWN || code == SDL_SCANCODE_S)
      flags &= ~PLAYER_FLAG_MOVE_DOWN;
    if (code == SDL_SCANCODE_RIGHT || code == SDL_SCANCODE_D)
      flags &= ~PLAYER_FLAG_MOVE_RIGHT;
    if (code == SDL_SCANCODE_LEFT || code == SDL_SCANCODE_A)
      flags &= ~PLAYER_FLAG_MOVE_LEFT;
  } break;
  }
  set_player_flags(player, flags);
  return 0;
}

Game *game_create(Window *window) {
  Game *game = malloc(sizeof(Game));
  game->window = window;
  game->world = world_create(get_window_renderer(window));
  Player *selfPlayer = player_create();
  game->selfPlayerId = world_add_player(game->world, selfPlayer);
  world_load_level(game->world, "default", "default");

  for (int i = 0; i < 50; i++) {
    Mob *mob = mob_create();
    world_add_mob(game->world, mob);
    mob_set_coord(mob, (SDL_Point){(rand() % 32) * 32, (rand() % 32) * 32});
  }
  return game;
}

void game_destroy(Game *game) {
  world_destroy(game->world);
  free(game);
}

void game_update(Game *game, float dt) { world_update(game->world, dt); }

void game_render(Game *game) {
  SDL_Renderer *renderer = get_window_renderer(game->window);
  SDL_RenderClear(renderer);

  Player *self_player = game_get_self_player(game);
  SDL_Point pivot = player_get_coord(self_player);
  pivot.x -= window_get_width(game->window) / 2;
  pivot.y -= window_get_height(game->window) / 2;

  world_render(game->world, pivot);

  SDL_RenderPresent(renderer);
}

void game_run(Game *game) {
  Window *window = game->window;
  float lastTime = (float)SDL_GetTicks() / 1000.0f;
  while (!window_event_loop(window, window_event_callback, game)) {
    float currentTime = (float)SDL_GetTicks() / 1000.0f;
    float deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    game_update(game, deltaTime);
    game_render(game);
  }
}

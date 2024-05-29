#include "../../lib/misc.h"
#include "entity/player.h"
#include "net/network.h"
#include "projectile/projectile.h"
#include "projectile/tomato.h"
#include "ui/canvas.h"
#include "ui/menu.h"
#include "window/window.h"
#include "ui/game_over.h"
#include "world/world.h"
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

typedef struct {
  Window *window;
  World *world;
  Canvas *canvas;
  Network *network;
  Menu *menu;
  GameOverScreen *game_over_screen;
  int in_menu;
  int game_over;
} Game;

Window *get_game_window(const Game *game) { return game->window; }
World *game_get_world(Game *game) { return game->world; }
Network *game_get_network(Game *game) { return game->network; }

int window_event_callback(SDL_Event const *event, void *arg) {
  Game *game = arg;
  if (event->type == SDL_QUIT) {
    return 1;
  }

  Player *player = world_get_self_player(game->world);
  PlayerFlag flags = get_player_flags(player);

  if(game->game_over) {
    if(event->type == SDL_KEYDOWN && event->key.keysym.sym==SDLK_RETURN) {
      Player *self_player = world_get_self_player(game->world);
      player_respawn(self_player, 1500, 1500);
      player_set_health(player, 100);
      game->game_over = 0;
    }
    return 0;
  }

  if (game->in_menu) {
    int action = menu_handle_event(game->menu, (SDL_Event *)event);
    if (action == 1) {
      const char *ip = menu_get_ip(game->menu);
      const char *ports = menu_get_port(game->menu);
      int port = atoi(ports);
      game->network = network_create(ip, port);
      game->in_menu = 0;
    } else if (action == -1) {
      return 1;
    }
    return 0;
  }

  switch (event->type) {
  case SDL_MOUSEBUTTONDOWN: {
    float middleX = window_get_width(game->window) / 2.0f;
    float middleY = window_get_height(game->window) / 2.0f;
    float x = event->motion.x - middleX;
    float y = event->motion.y - middleY;
    int length = vector_length(x, y);
    SDL_FPoint direction = (SDL_FPoint){x / length, y / length};
    x = direction.x * 50;
    y = direction.y * 50;
    SDL_Point pivot = player_get_coord(player);
    x += pivot.x;
    y += pivot.y;

    TomatoProjectile *tomato =
        tomatoprojectile_create(direction, (SDL_Point){x, y});
    Projectile *tomatoProjectile = tomatoprojectile_get_projectile(tomato);
    world_add_projectile(game->world, tomatoProjectile);
    world_add_collider(game->world, projectile_get_collider(tomatoProjectile));
    network_send_projectile(game, tomatoProjectile);
  } break;
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
  game->canvas = canvas_create();
  game->world = world_create(get_window_renderer(window));
  world_load_level(game->world, "dungeon", "dungeon");
  game->network = NULL;
  game->menu = menu_create(get_window_renderer(window));
  game->game_over_screen = game_over_screen_create(get_window_renderer(window), "Press Enter to respawn", "assets/fonts/sans.ttf", 48);
  game->in_menu = 1;
  game->game_over = 0;
  
  return game;
}

void game_destroy(Game *game) {
  if (game->network) {
    network_destroy(game->network);
  }
  world_destroy(game->world);
  free(game);
}

void game_update(Game *game, float dt) {
  if(game->game_over) {
    return;
  }
  if (!game->in_menu) {
    world_update(game->world, dt);
    network_update(game->network, game);
  }
  Player *self_player = world_get_self_player(game->world);
  if(player_get_health(self_player) <= 0) {
    game->game_over = 1;
  }
}

Player *game_get_self_player(Game *game) {
  return world_get_self_player(game->world);
}

void game_render(Game *game) {
  SDL_Renderer *renderer = get_window_renderer(game->window);
  SDL_RenderClear(renderer);
  if(game->game_over) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    game_over_screen_draw(game->game_over_screen);
    SDL_RenderPresent(renderer);
    return;
  }

  if (game->in_menu) {
    menu_render(game->menu, renderer);
    SDL_RenderPresent(renderer);
    return;
  }

  Player *self_player = world_get_self_player(game->world);
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

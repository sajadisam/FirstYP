#ifndef GAME_H
#define GAME_H

#include "entity/player.h"
#include "window/window.h"
#include "world/world.h"
#include <SDL2/SDL_render.h>

typedef struct Game Game;

Game *game_create(Window *window);
void game_destroy(Game *game);
void game_run(Game *game);
void game_update(Game *game, float dt);
void game_render(Game *game);
Window *get_game_window(const Game *game);
Player *game_get_self_player(Game *game);
World *game_get_world(Game *game);
void *game_get_network(Game *game);

#endif // GAME_H

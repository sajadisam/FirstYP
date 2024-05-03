#ifndef _GAME_
#define _GAME_

#include "clock.h"
#include "player/player.h"
#include "window/window.h"
#include <SDL2/SDL_render.h>

enum GameState {
  Paused,
  Processing,
  Exiting,
};

// Struct that defines our overall game data
typedef struct game Game;

/*
 * Create an instance of our game
 */
Game *create_game(Window *window, Player *player, struct Sprite *map,
                  Clock *clock);

SDL_Renderer *get_game_renderer(const Game *game);
Window *get_game_window(const Game *game);
Player *get_game_player(const Game *game);
Clock *get_game_clock(const Game *game);
struct Sprite *get_game_map(const Game *game);

#endif // !_GAME_

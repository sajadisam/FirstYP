#ifndef _GAME_
#define _GAME_

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

SDL_Renderer *get_game_renderer(Game *game);
SDL_Window *get_game_sdlwindow(Game *game);

/*
 * Create an instance of our game
 */
Game *create_game(Window *window, Player *player);

#endif // !_GAME_

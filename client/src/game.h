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
typedef struct gameSprite GameSprite;

/*
 * Create an instance of our game
 */
Game *create_game(Window *window, Player *player, Clock *clock);

struct Sprite *find_game_sprite(Game *game, const char *id);
struct Sprite *add_game_sprite(Game *game, struct Sprite *sprite,
                               const char *id);

void render_game_sprites(Game *game);
SDL_Renderer *get_game_renderer(const Game *game);
Window *get_game_window(const Game *game);
Player *get_game_player(const Game *game);
Clock *get_game_clock(const Game *game);
struct Sprite *get_game_map(const Game *game);

#endif // !_GAME_

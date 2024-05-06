#ifndef GAME_H
#define GAME_H

#include "entity/player.h"
#include "window/window.h"
#include <SDL2/SDL_render.h>

typedef struct Game Game;

/// @brief Create a game
/// @param window The window to create the game
/// @return The game created
Game *game_create(Window *window);

/// @brief Destroy a game
/// @param game The game to destroy
void game_destroy(Game *game);

/// @brief Run the game
/// @param game The game to run
void game_run(Game *game);

/// @brief Update the game
/// @param game The game to update
/// @param dt The delta time
void game_update(Game *game, float dt);

/// @brief Render the game
/// @param game The game to render
void game_render(Game *game);

/// @brief Get the window from the game
/// @param game The game to get the window
/// @return The window from the game
Window *get_game_window(const Game *game);

/// @brief Get the player from the game
/// @param game The game to get the player
/// @return The player from the game
Player *game_get_self_player(Game *game);

#endif // GAME_H

#ifndef _PLAYER_
#define _PLAYER_

#include "../clock.h"
#include "player_flags.h"
#include <SDL2/SDL_rect.h>

/*
 * Player struct that holds all data for a single player
 */
typedef struct player Player;

/*
 * Create a player
 */
Player *create_player(struct SpriteSheet *sprite);

/*
 * Destroy a player
 */
void destroy_player(Player *player);

void perform_movement(Player *player, Timer *animation_speed);

struct SpriteSheet *get_player_spritesheet(const Player *player);

PlayerFlag get_player_flags(const Player *player);
void set_player_flags(Player *player, PlayerFlag flags);
SDL_Point get_player_coordinates(const Player *player);
void set_player_coordinates(Player *player, const SDL_Point coordinate);

void player_move_up(Player *player);
void player_move_down(Player *player);
void player_move_right(Player *player);
void player_move_left(Player *player);

#endif // !_PLAYER_

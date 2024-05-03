#ifndef _PLAYER_
#define _PLAYER_

#include "player_flags.h"
#include <SDL2/SDL_rect.h>

/*
 * Player struct that holds all data for a single player
 */
typedef struct player Player;

struct SpriteSheet *get_player_spritesheet(Player *player);

PlayerFlag get_player_flags(Player *player);
void set_player_flags(Player *player, PlayerFlag flags);
SDL_Point get_player_coordinates(Player *player);
void set_player_coordinates(Player *player, SDL_Point coordinate);

void player_move_up(Player *player);
void player_move_down(Player *player);
void player_move_right(Player *player);
void player_move_left(Player *player);

/*
 * Create a player
 */
Player *create_player(struct SpriteSheet *sprite);

/*
 * Create a networkable player
 */
void destroy_player(Player *player);

#endif // !_PLAYER_

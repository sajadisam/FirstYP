#ifndef PLAYER_H
#define PLAYER_H

#include "SDL2/SDL_rect.h"
#include "player_common.h"

typedef struct Player Player;

Player *player_create();
void player_destroy(Player *player);

void player_update(Player *player, float dt);
void player_update_direction(Player *player);
void player_update_movement(Player *player, float dt);

PlayerFlag get_player_flags(const Player *player);
void set_player_flags(Player *player, PlayerFlag flags);
SDL_Point player_get_coord(const Player *player);
int player_get_draw_frame_id(Player const *player);
void player_set_id(Player *player, int id);

#endif // PLAYER_H

#ifndef _NetPlayer_
#define _NetPlayer_

#include "../world/world.h"

void net_player_join(World *world, int id);
void net_player_player_move(World *world, int id, int x, int y);
void net_player_connected(World *world, int id);
void net_player_react(World *world, const char *message);

#endif // !_NetPlayer_

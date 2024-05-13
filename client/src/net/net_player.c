#include "../../../lib/debug.h"
#include "../../../lib/network_constants.h"
#include "../entity/player.h"
#include "../world/world.h"
#include <stdio.h>

void net_player_disconnect(World *world, int id) {
  Player *player = world_get_player_from_id(world, id);
  world_remove_player(world, player);
}

void net_player_join(World *world, int id) {
  Player *player = player_create();
  player_set_id(player, id);
  world_add_player(world, player);
}

void net_player_player_move(World *world, int id, int x, int y, int flags) {
  Player *player = world_get_player_from_id(world, id);
  if (player) {
    player_set_flags(player, flags);
    player_set_coord(player, x, y);
  }
}

void net_player_connected(World *world, int id) {
  Player *self = world_get_self_player(world);
  player_set_id(self, id);
}

void net_player_react(World *world, const char *message) {
  Opcode opcode;
  sscanf(message, "%d ", &opcode);
  switch (opcode) {
  case OPCODE_CONNECTED: {
    int id;
    sscanf(message, "%d %d ", &opcode, &id);
    net_player_connected(world, id);
  } break;
  case OPCODE_JOINED: {
    int id;
    sscanf(message, "%d %d ", &opcode, &id);
    net_player_join(world, id);
  } break;
  case OPCODE_DISCONNECT: {
    int id;
    sscanf(message, "%d %d ", &opcode, &id);
    net_player_disconnect(world, id);
  } break;
  case OPCODE_PLAYERMOVE: {
    int id, x, y, flags;
    sscanf(message, "%d %d %d %d %d ", &opcode, &id, &x, &y, &flags);
    net_player_player_move(world, id, x, y, flags);
  } break;
  }
}

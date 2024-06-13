#include "../../../lib/debug.h"
#include "../../../lib/network_constants.h"
#include "../entity/player.h"
#include "../game.h"
#include "../world/world.h"
#include "net_player.h"
#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <string.h>

#define MAX_CLIENTS 100

typedef struct {
  TCPsocket socket;
  SDLNet_SocketSet socket_set;
} Network;

void network_send(Network *network, const char *data) {
  int len = strlen(data);
  int sent = SDLNet_TCP_Send(network->socket, data, len);
  if (sent < len) {
    WARN("Failed to send message\n");
  }
}

Network *network_create(const char *host, int port) {
  Network *network = malloc(sizeof(Network));
  network->socket_set = SDLNet_AllocSocketSet(MAX_CLIENTS);
  IPaddress ip;

  if (SDLNet_ResolveHost(&ip, host, port)) {
    ERR("Failed to connect to %s\n", host);
    return NULL;
  }

  network->socket = SDLNet_TCP_Open(&ip);
  if (!network->socket) {
    ERR("Couldn't open TCP connection with %s\n", host);
    return NULL;
  }
  SDLNet_AddSocket(network->socket_set, (SDLNet_GenericSocket)network->socket);
  return network;
}

void network_update_player_movement(Game *game) {
  Network *network = game_get_network(game);
  Player *self = world_get_self_player(game_get_world(game));
  PlayerFlag selfFlag = player_get_flags(self);
  if (selfFlag & PLAYER_FLAG_MOVE_ANY) {
    char buffer[1024];
    SDL_Point coord = player_get_coord(self);
    sprintf(buffer, "%d %d %d %d %d ", OPCODE_PLAYERMOVE, player_get_id(self),
            coord.x, coord.y, selfFlag);
    if (network->socket)
      SDLNet_TCP_Send(network->socket, buffer, 1024);
  }
}

void network_update(Network *network, Game *game) {
  network_update_player_movement(game);

  if (!(SDLNet_CheckSockets(network->socket_set, 0) > 0))
    return;

  if (!SDLNet_SocketReady(network->socket))
    return;
  char message[1024];
  int len = SDLNet_TCP_Recv(network->socket, message, 1024);
  if (len <= 0) {
  } else {
    net_player_react(game_get_world(game), message);
  }
}

void network_destroy(Network *network) { free(network->socket); }

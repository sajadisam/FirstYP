#include "../debug.h"
#include "../entity/player.h"
#include "../world/world.h"
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

void network_update(Network *network, World *world) {
  if (!(SDLNet_CheckSockets(network->socket_set, 0) > 0))
    return;
  if (!SDLNet_SocketReady(network->socket))
    return;
  char message[1024];
  int len = SDLNet_TCP_Recv(network->socket, message, 1024);
  if (len <= 0) {
  } else {
    DEBUG("RECEIVED: %s\n", message);
    Player *player = player_create();
    int id = 0;
    char opcode[1024];
    sscanf(message, "%s %d", opcode, &id);
    player_set_id(player, id);
    world_add_player(world, player);
  }
}

void network_destroy(Network *network) { free(network->socket); }

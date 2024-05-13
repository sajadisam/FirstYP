#include "../debug.h"
#include "../game.h"
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

void network_update(Network *network, Game *game) {
  if (!network || !(SDLNet_CheckSockets(network->socket_set, 0) > 0))
    return;
  if (SDLNet_SocketReady(network->socket)) {
    char message[1024];
    int len = SDLNet_TCP_Recv(network->socket, message, 1024);
    DEBUG("received: %s\n", message);
  } else {
    DEBUG("Message received\n");
  }
}

void network_destroy(Network *network) { free(network->socket); }

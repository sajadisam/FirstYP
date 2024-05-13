#include "../../lib/debug.h"
#include "../../lib/misc.h"
#include <SDL2/SDL_net.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  int id;
  TCPsocket socket;
  IPaddress *ip;
} Client;

Client *client_create(TCPsocket socket) {
  Client *client = malloc(sizeof(Client));
  client->id = randomi32(0, 1000000);
  client->socket = socket;
  client->ip = SDLNet_TCP_GetPeerAddress(client->socket);
  if (!client->ip) {
    WARN("Failed to get remote ip of a client: '%s'\n", SDLNet_GetError());
    return NULL;
  }

  return client;
}

TCPsocket client_get_socket(Client *client) { return client->socket; }
IPaddress *client_get_ip(Client *client) { return client->ip; }
int client_get_id(Client *client) { return client->id; }

bool client_send_message(Client *client, const char *message, int len) {
  SDLNet_TCP_Send(client->socket, message, 1024);
  return true;
}

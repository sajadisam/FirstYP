#include "../../lib/debug.h"
#include "../../lib/network_constants.h";
#include "client.h"
#include <SDL2/SDL_net.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 100

typedef struct {
  TCPsocket server;
  Client *clients[100];
  int clients_connected;
  SDLNet_SocketSet socket_set;
} Server;

Server *server_create(const char *host, int port) {
  Server *server = malloc(sizeof(Server));
  server->clients_connected = 0;
  server->socket_set = SDLNet_AllocSocketSet(MAX_CLIENTS + 1);
  IPaddress ip;
  if (SDLNet_ResolveHost(&ip, NULL, 3030) == -1) {
    ERR("Failed to resolve host '%s'\n", SDLNet_GetError());
    return NULL;
  }

  server->server = SDLNet_TCP_Open(&ip);
  if (!server->server) {
    ERR("Failed to open TCP '%s'\n", SDLNet_GetError());
    return NULL;
  }
  SDLNet_AddSocket(server->socket_set, (SDLNet_GenericSocket)server->server);
  return server;
}

TCPsocket server_get_socket(Server *server) { return server->server; }
SDLNet_SocketSet server_get_socket_set(Server *server) {
  return server->socket_set;
}

int server_get_client_size(Server *server) { return server->clients_connected; }

Client *server_get_client(Server *server, int index) {
  return server->clients[index];
}

void server_add_client(Server *server) {
  TCPsocket socket = SDLNet_TCP_Accept(server->server);
  if (!socket) {
    SDL_Delay(100);
    return;
  }

  Client *client = client_create(socket);
  int clientID = client_get_id(client);
  IPaddress *ip = client_get_ip(client);

  Uint32 ipaddr = SDL_Swap32(ip->host);
  char message[1024];
  sprintf(message, "%d %d", OPCODE_CONNECTED, clientID);
  client_send_message(client, message);

  // Report to client about all other clients
  for (int i = 0; i < server->clients_connected; i++) {
    Client *target = server->clients[i];
    char message[1024];
    sprintf(message, "%d %d", OPCODE_JOINED, client_get_id(target));
    client_send_message(client, message);
  }

  // Report to other clients about new client
  for (int i = 0; i < server->clients_connected; i++) {
    Client *target = server->clients[i];
    char message[1024];
    int targetID = client_get_id(target);
    sprintf(message, "%d %d", OPCODE_JOINED, clientID);
    client_send_message(target, message);
  }

  server->clients[server->clients_connected] = client;
  server->clients_connected++;

  INFO("Accepted a connection from %d.%d.%d.%d on port %hu with %d users id: "
       "%d\n",
       ipaddr >> 24, (ipaddr >> 16) & 0xFF, (ipaddr >> 8) & 0xFF, ipaddr & 0xFF,
       ip->port, server->clients_connected, clientID);
  SDLNet_AddSocket(server->socket_set, (SDLNet_GenericSocket)socket);
}

void handle_client_disconnection(Server *server, Client *client) {
  TCPsocket socket = client_get_socket(client);
  SDLNet_TCP_DelSocket(server->socket_set, socket);
  SDLNet_TCP_Close(socket);
  for (int i = 0; i < server->clients_connected; i++) {
    Client *target = server->clients[i];
    int clientID = client_get_id(client);
    if (client_get_id(target) == clientID) {
      DEBUG("Closing client: index(%d) id(%d) total(%d)\n", i, clientID,
            server->clients_connected);
      for (int x = i; x < server->clients_connected - 1; x++) {
        WARN("swapping clients: %d\n", server->clients_connected);
        server->clients[x] = server->clients[x + 1];
      }
    }
  }
  server->clients_connected--;
}

void handle_client_message(Server *server, Client *client, char msg[1024],
                           int len) {
  for (int i = 0; i < server->clients_connected; i++) {
    Client *target = server->clients[i];
    int clientID = client_get_id(client);
    if (client_get_id(target) != clientID)
      SDLNet_TCP_Send(client_get_socket(target), msg, len);
  }
  INFO("Received: %s\n", msg);
}

void server_run(Server *server) {
  for (int i = 0; i < server->clients_connected; i++) {
    Client *client = server->clients[i];
    TCPsocket socket = client_get_socket(client);
    if (!socket)
      continue;
    if (SDLNet_SocketReady(socket)) {
      char message[1024];
      int len = SDLNet_TCP_Recv(socket, message, 1024);
      if (len <= 0) {
        handle_client_disconnection(server, client);
        break;
      }
      handle_client_message(server, client, message, len);
    }
  }
}

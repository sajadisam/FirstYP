#include "shared/src/debug.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_endian.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_net.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TODO(Xelian): Add mobs to server

#define MAX_CLIENTS 100

typedef struct {
  int id;
  TCPsocket socket;
} Client;

typedef struct {
  TCPsocket socket;
  Client clients[MAX_CLIENTS];
  int clients_connected;
  SDLNet_SocketSet socket_set;
} Server;

int randomi32(int min, int max) { return rand() % (max + 1 - min) + min; }

void add_client(Server *server, Client *client) {
  client->socket = SDLNet_TCP_Accept(server->socket);
  if (!client->socket) {
    SDL_Delay(100);
    return;
  }
  client->id = randomi32(0, 1000000000);
  IPaddress *remoteIp = SDLNet_TCP_GetPeerAddress(client->socket);
  if (!remoteIp) {
    WARN("Failed to get remote ip of a client: '%s'\n", SDLNet_GetError());
    return;
  }

  Uint32 ipaddr = SDL_Swap32(remoteIp->host);
  INFO("Accepted a connection from %d.%d.%d.%d on port %hu with %d users\n",
       ipaddr >> 24, (ipaddr >> 16) & 0xFF, (ipaddr >> 8) & 0xFF, ipaddr & 0xFF,
       remoteIp->port, server->clients_connected);

  SDLNet_AddSocket(server->socket_set, (SDLNet_GenericSocket)client->socket);
  server->clients_connected++;
}

void handle_client_disconnection(Server *server, Client *client) {
  // User disconnected
  SDLNet_TCP_DelSocket(server->socket_set, client->socket);
  SDLNet_TCP_Close(client->socket);
  for (int i = 0; i < server->clients_connected; i++) {
    Client *target = &server->clients[i];
    if (target->id == client->id) {
      DEBUG("Closing client: index(%d) id(%d) total(%d)\n", i, client->id,
            server->clients_connected);

      for (int x = i; x < server->clients_connected; x++) {
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
    Client *target = &server->clients[i];
    if (target->id != client->id)
      SDLNet_TCP_Send(target->socket, msg, len);
  }
  INFO("Recieved: %s\n", msg);
}

void client_loop(Server *server, Client *client) {
  for (int i = 0; i < server->clients_connected; i++) {
    Client *client = &server->clients[i];
    if (client->socket == NULL)
      continue;
    if (SDLNet_SocketReady(client->socket)) {
      char message[1024];
      int len = SDLNet_TCP_Recv(client->socket, message, 1024);
      if (len <= 0) {
        handle_client_disconnection(server, client);
        break;
      }
      handle_client_message(server, client, message, len);
    }
  }
}

int main() {
  Server server;
  server.clients_connected = 0;
  server.socket_set = SDLNet_AllocSocketSet(MAX_CLIENTS + 1);
  srand(time(NULL));

  if (SDL_Init(0) == -1) {
    ERR("Failed to initialize SDL '%s'\n", SDL_GetError());
    return 1;
  }
  if (SDLNet_Init() == -1) {
    ERR("Failed to initialize SDL '%s'\n", SDL_GetError());
    return 1;
  }

  INFO("Server starting up...\n");

  IPaddress ip;
  if (SDLNet_ResolveHost(&ip, NULL, 3030) == -1) {
    ERR("Failed to resolve host '%s'\n", SDLNet_GetError());
    return 1;
  }

  server.socket = SDLNet_TCP_Open(&ip);
  if (!server.socket) {
    ERR("Failed to open TCP '%s'\n", SDLNet_GetError());
    return 1;
  }

  SDLNet_AddSocket(server.socket_set, (SDLNet_GenericSocket)server.socket);

  while (true) {
    if (!(SDLNet_CheckSockets(server.socket_set, -1) > 0))
      continue;
    if (SDLNet_SocketReady(server.socket)) {
      int *connected = &server.clients_connected;
      Client *client = &server.clients[*connected];
      add_client(&server, client);
    } else {
      for (int i = 0; i < server.clients_connected; i++) {
        Client *client = &server.clients[i];
        if (SDLNet_SocketReady(client->socket))
          client_loop(&server, client);
      }
    }
  }

  SDLNet_Quit();
  SDL_Quit();
  return 0;
}

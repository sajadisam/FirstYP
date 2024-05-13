#include "../../lib/debug.h"
#include "server.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

int main() {
  srand(time(NULL));
  if (SDL_Init(0) == -1) {
    ERR("Failed to initialize SDL '%s'\n", SDL_GetError());
    return 1;
  }
  if (SDLNet_Init() == -1) {
    ERR("Failed to initialize SDL '%s'\n", SDL_GetError());
    return 1;
  }

  Server *server = server_create();
  INFO("Server is now up\n");
  while (true) {
    if (!(SDLNet_CheckSockets(server_get_socket_set(server), 0) > 0))
      continue;
    if (SDLNet_SocketReady(server_get_socket(server))) {
      server_add_client(server);
    } else {
      server_run(server);
    }
  }

  SDLNet_Quit();
  SDL_Quit();
  return 0;
}

#include "player.h"
#include <SDL2/SDL_net.h>
#include <stdlib.h>

typedef struct {
  int id;
  TCPsocket socket;
  Player *player;
} NetPlayer;

NetPlayer *create_net_player() {
  NetPlayer *player = malloc(sizeof(NetPlayer));
  player->player = create_player();
  return player;
}

void destroy_net_player(NetPlayer *player) {
  // Free player and then the NetPlayer
  if (player) {
    destroy_player(player->player);
    free(player);
    player = NULL;
  }
}

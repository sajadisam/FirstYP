#ifndef _NET_
#define _NET_

#include "../world/world.h"
typedef struct network Network;

Network *network_create(const char *host, int port);
void network_update(Network *network, void *game);
void network_destroy(Network *network);
void network_send(Network *network, const char *data);
void network_update_player_movement(void *game);
void network_send_projectile(void *game, Projectile *projectile);

#endif // !_NET_

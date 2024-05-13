#ifndef _NET_
#define _NET_

#include "../world/world.h"
typedef struct network Network;

Network *network_create(const char *host, int port);
void network_update(Network *network, World *world);
void network_destroy(Network *network);

#endif // !_NET_

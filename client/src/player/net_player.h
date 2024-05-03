
#ifndef _NET_PLAYER_
#define _NET_PLAYER_

/*
 * Create a composed net player from player
 */
typedef struct netPlayer NetPlayer;

/*
 * Create a networkable player
 */
NetPlayer *create_net_player(struct SpriteSheet *sprite);

/*
 * Destroy our networkable player
 */
void destroy_net_player(NetPlayer *player);

#endif // !_NET_PLAYER_

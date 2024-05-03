#ifndef _PLAYER_
#define _PLAYER_

/*
 * Player struct that holds all data for a single player
 */
typedef struct player Player;

struct SpriteSheet *get_player_spritesheet(Player *player);

/*
 * Create a player
 */
Player *create_player(struct SpriteSheet *sprite);

/*
 * Create a networkable player
 */
void destroy_player(Player *player);

#endif // !_PLAYER_

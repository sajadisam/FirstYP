#ifndef _PLAYER_
#define _PLAYER_

/*
 * Player struct that holds all data for a single player
 */
typedef struct player Player;

/*
 * Create a player
 */
Player *create_player();

/*
 * Create a networkable player
 */
void destroy_player(Player *);

#endif // !_PLAYER_

#ifndef _SETUP_
#define _SETUP_

typedef struct game Game;
void initalize_sdl();

Game *initialize();
void run(Game *game);
void shutdown(Game *game);
#endif // !_SETUP_

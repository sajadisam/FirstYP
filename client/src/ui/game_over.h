#ifndef GAME_OVER_H
#define GAME_OVER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct GameOverScreen GameOverScreen;

GameOverScreen *game_over_screen_create(SDL_Renderer *renderer, const char *text, const char *font_path, int font_size);
void game_over_screen_destroy(GameOverScreen *screen);
void game_over_screen_draw(GameOverScreen *screen);

#endif // GAME_OVER_H

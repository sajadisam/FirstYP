// menu.h
#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef enum {
    MAIN_MENU,
    GAME_RUNNING,
    GAME_EXIT
} GameState;

// Function prototypes
void menuInit(SDL_Renderer* renderer, TTF_Font* font);
int menuLoop(SDL_Renderer* renderer);
void menuCleanup();

#endif
// menu.c
#include "menu.h"
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

static SDL_Texture *backgroundTexture = NULL;
static SDL_Rect playButton, quitButton;
static TTF_Font *menuFont = NULL;

void menuInit(SDL_Renderer* renderer, TTF_Font* font) {
    menuFont = font;

    // Load the background image
    backgroundTexture = IMG_LoadTexture(renderer, "./resources/menu_Background.png");
    if (!backgroundTexture) {
        printf("Failed to load background texture: %s\n", SDL_GetError());
        return;
    }

    // Set up buttons
    playButton = (SDL_Rect){70, 230, 100, 50};
    quitButton = (SDL_Rect){430, 230, 100, 50};
}

void drawTextButton(SDL_Renderer* renderer, SDL_Rect buttonRect, const char* text, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(menuFont, text, color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &buttonRect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int menuLoop(SDL_Renderer* renderer) {
    SDL_Event e;
    SDL_Color white = {255, 255, 255, 255};

    while (true) {  // Change this loop to not use a quit variable
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                return GAME_EXIT;  // Indicate to exit the game
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (SDL_PointInRect(&(SDL_Point){x, y}, &playButton)) {
                    return GAME_RUNNING;  // Indicate to start the game
                } else if (SDL_PointInRect(&(SDL_Point){x, y}, &quitButton)) {
                    return GAME_EXIT;  // Indicate to exit the game
                }
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        drawTextButton(renderer, playButton, "Play", white);
        drawTextButton(renderer, quitButton, "Quit", white);
        SDL_RenderPresent(renderer);
    }
}

void menuCleanup() {
    if (backgroundTexture) {
        SDL_DestroyTexture(backgroundTexture);
        backgroundTexture = NULL;
    }
}
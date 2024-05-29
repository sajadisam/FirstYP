#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
    TTF_Font *font;
    SDL_Renderer *renderer;
} GameOverScreen;

GameOverScreen *game_over_screen_create(SDL_Renderer *renderer, const char *text, const char *font_path, int font_size) {
    GameOverScreen *screen = (GameOverScreen *)malloc(sizeof(GameOverScreen));
    screen->renderer = renderer;

    screen->font = TTF_OpenFont(font_path, font_size);
    if (!screen->font) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        free(screen);
        return NULL;
    }

    SDL_Color color = {255, 255, 255, 255};
    SDL_Surface *surface = TTF_RenderText_Solid(screen->font, text, color);
    screen->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    screen->rect = (SDL_Rect){200, 200, surface->w, surface->h};

    return screen;
}

void game_over_screen_destroy(GameOverScreen *screen) {
    SDL_DestroyTexture(screen->texture);
    TTF_CloseFont(screen->font);
    free(screen);
}

void game_over_screen_draw(GameOverScreen *screen) {
    SDL_RenderCopy(screen->renderer, screen->texture, NULL, &screen->rect);
}

#include "text.h"
#include "canvas.h"
#include "button.h"
#include "element.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    Canvas *canvas;
    Element *play_button_element;
    Element *exit_button_element;
    Element *ip_element;
    Element *port_element;
    SDL_Texture *background_texture;
    char ip_address[16];
    char port[6];
    int active;
} Menu;

SDL_Texture *load_texture(const char *file, SDL_Renderer *renderer) {
    SDL_Texture *texture = NULL;
    SDL_Surface *loaded_image = IMG_Load(file);
    if (loaded_image == NULL) {
        fprintf(stderr, "SDL img error: %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, loaded_image);
    SDL_FreeSurface(loaded_image);
    if (texture == NULL) {
        fprintf(stderr, "SDL img error: %s", SDL_GetError());
    }
    return texture;
}

Menu *menu_create(SDL_Renderer *renderer) {
    Menu *menu = malloc(sizeof(Menu));
    menu->canvas = canvas_create();
    menu->background_texture = load_texture("assets/images/tomario.png", renderer);

    TTF_Font *font = TTF_OpenFont("assets/fonts/sans.ttf", 24);
    if (!font) {
        fprintf(stderr, "Failed to load font: %s", SDL_GetError());
        free(menu);
        return NULL;
    }

    SDL_Color normal_color = {100, 150, 255, 255};
    SDL_Color hover_color = {255, 100, 100, 255};

    SDL_Rect play_rect = {350, 200, 200, 50};
    Button *play_button = button_create(renderer, "Play Game", font, normal_color, hover_color, play_rect, NULL, NULL);
    menu->play_button_element = element_create(play_rect, (void (*)(void *))button_draw, play_button);

    SDL_Rect exit_rect = {350, 300, 200, 50};
    Button *exit_button = button_create(renderer, "Exit Game", font, normal_color, hover_color, exit_rect, NULL, NULL);
    menu->exit_button_element = element_create(exit_rect, (void (*)(void *))button_draw, exit_button);

    strcpy(menu->ip_address, "127.0.0.1");
    strcpy(menu->port, "3030");

    SDL_Color text_color = {255, 255, 255, 255};

    Text *ip_text = text_create(renderer, "IP Address: 127.0.0.1", "assets/fonts/sans.ttf", 24);
    text_set_color(ip_text, text_color);
    text_set_coordinate(ip_text, (SDL_Point){220, 405});
    menu->ip_element = text_get_element(ip_text);

    Text *port_text = text_create(renderer, "Port: 3030", "assets/fonts/sans.ttf", 24);
    text_set_color(port_text, text_color);
    text_set_coordinate(port_text, (SDL_Point){220, 455});
    menu->port_element = text_get_element(port_text);

    canvas_add_element(menu->canvas, menu->play_button_element);
    canvas_add_element(menu->canvas, menu->exit_button_element);
    canvas_add_element(menu->canvas, menu->ip_element);
    canvas_add_element(menu->canvas, menu->port_element);

    menu->active = 0;

    TTF_CloseFont(font);

    return menu;
}

void menu_destroy(Menu *menu) {
    if (menu->background_texture) {
        SDL_DestroyTexture(menu->background_texture);
    }
    button_destroy((Button *)element_get_coomponent(menu->play_button_element));
    button_destroy((Button *)element_get_coomponent(menu->exit_button_element));
    canvas_destroy(menu->canvas);
    free(menu);
}

void update_text_element(Element *element, const char *new_text, SDL_Renderer *renderer) {
    Text *text = (Text *)element_get_coomponent(element);
    text_set_text(text, new_text);
    text_update(text);
}

void menu_render(Menu *menu, SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);

    if (menu->background_texture) {
        SDL_RenderCopy(renderer, menu->background_texture, NULL, NULL);
    }

    SDL_SetRenderDrawColor(renderer, 100, 150, 255, 255);
    SDL_Rect ip_bar_rect = {200, 400, 400, 40};
    SDL_RenderFillRect(renderer, &ip_bar_rect);
    SDL_Rect port_bar_rect = {200, 450, 400, 40};
    SDL_RenderFillRect(renderer, &port_bar_rect);

    char ip_display[32];
    snprintf(ip_display, sizeof(ip_display), "IP Address: %s", menu->ip_address);
    update_text_element(menu->ip_element, ip_display, renderer);

    char port_display[32];
    snprintf(port_display, sizeof(port_display), "Port: %s", menu->port);
    update_text_element(menu->port_element, port_display, renderer);

    canvas_render(menu->canvas);

    element_draw(menu->play_button_element);
    element_draw(menu->exit_button_element);

    SDL_RenderPresent(renderer);
}

int menu_handle_event(Menu *menu, SDL_Event *event) {
    Button *play_button = (Button *)element_get_coomponent(menu->play_button_element);
    Button *exit_button = (Button *)element_get_coomponent(menu->exit_button_element);

    if (button_handle_event(play_button, event)) {
        menu->active = 1;
        return 1;
    }
    if (button_handle_event(exit_button, event)) {
        menu->active = -1;
        return -1;
    }

    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int x = event->button.x;
        int y = event->button.y;

        SDL_Rect ip_rect = element_get_rect(menu->ip_element);
        if (x >= ip_rect.x && x <= ip_rect.x + ip_rect.w &&
            y >= ip_rect.y && y <= ip_rect.y + ip_rect.h) {
            menu->active = 1;
            return 0;
        }

        SDL_Rect port_rect = element_get_rect(menu->port_element);
        if (x >= port_rect.x && x <= port_rect.x + port_rect.w &&
            y >= port_rect.y && y <= port_rect.y + port_rect.h) {
            menu->active = 2;
            return 0;
        }
    } 
    else if (event->type == SDL_TEXTINPUT) {
        if (menu->active == 1 && strlen(menu->ip_address) < 15) // 15(?) 198.168.0.1 [xxxxxxxxxxxx]?
            strcat(menu->ip_address, event->text.text);
        else if (menu->active == 2 && strlen(menu->port) < 5) //space terminator
            strcat(menu->port, event->text.text);
    } 
    else if (event->type == SDL_KEYDOWN) {
        if (event->key.keysym.sym == SDLK_BACKSPACE) {
            if (menu->active == 1 && strlen(menu->ip_address) > 0)
                menu->ip_address[strlen(menu->ip_address) - 1] = '\0';
            else if (menu->active == 2 && strlen(menu->port) > 0)
                menu->port[strlen(menu->port) - 1] = '\0';
        }
    }
    return 0;
}

const char *menu_get_ip(Menu *menu) { return menu->ip_address; }
const char *menu_get_port(Menu *menu) { return menu->port; }

#include "button.h"
#include <stdlib.h>
#include <string.h>
#include "element.h"

struct Button {
    Element *element;
    SDL_Color color;
    SDL_Color hover_color;
    SDL_Texture *label_texture;
    int hover;
    void *userdata;
    void (*on_click)(void *userdata);
    SDL_Renderer *renderer;
};

void button_draw(void *component) {
    Button *button = (Button *)component;
    SDL_Color current_color = button->hover ? button->hover_color : button->color;
    SDL_SetRenderDrawColor(button->renderer, current_color.r, current_color.g, current_color.b, current_color.a);

    SDL_Rect rect = element_get_rect(button->element);
    SDL_RenderFillRect(button->renderer, &rect);

    int label_width, label_height;
    SDL_QueryTexture(button->label_texture, NULL, NULL, &label_width, &label_height);
    SDL_Rect label_rect = {
        .x = rect.x + (rect.w - label_width) / 2,
        .y = rect.y + (rect.h - label_height) / 2,
        .w = label_width,
        .h = label_height
    };
    SDL_RenderCopy(button->renderer, button->label_texture, NULL, &label_rect);
}

Button *button_create(SDL_Renderer *renderer, const char *label, TTF_Font *font, SDL_Color color,
                      SDL_Color hover_color, SDL_Rect rect, void (*on_click)(void *userdata), void *userdata) {
    Button *button = malloc(sizeof(Button));
    button->element = element_create(rect, button_draw, button);
    button->color = color;
    button->hover_color = hover_color;
    button->hover = 0;
    button->on_click = on_click;
    button->userdata = userdata;
    button->renderer = renderer;

    SDL_Surface *surface = TTF_RenderText_Solid(font, label, (SDL_Color){255, 255, 255, 255});
    button->label_texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return button;
}

void button_destroy(Button *button) {
    if (button->label_texture) {
        SDL_DestroyTexture(button->label_texture);
    }
    element_destroy(button->element);
    free(button);
}

int button_handle_event(Button *button, SDL_Event *event) {
    SDL_Rect rect = element_get_rect(button->element);
    if (event->type == SDL_MOUSEMOTION) {
        int x = event->motion.x;
        int y = event->motion.y;
        button->hover = SDL_PointInRect(&(SDL_Point){x, y}, &rect);
    } else if (event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && button->hover) {
        if (button->on_click) {
            button->on_click(button->userdata);
        }
        return 1;
    }
    return 0;
}

SDL_Texture* button_get_label_texture(Button *button) {
    return button->label_texture;
}

SDL_Rect button_get_rect(Button *button) {
    return element_get_rect(button->element);
}

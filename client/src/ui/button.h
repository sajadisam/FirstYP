#ifndef BUTTON_H
#define BUTTON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct Button Button;

Button *button_create(SDL_Renderer *renderer, const char *label, TTF_Font *font, SDL_Color color,
                      SDL_Color hover_color, SDL_Rect rect, void (*on_click)(void *userdata), void *userdata);

void button_destroy(Button *button);
int button_handle_event(Button *button, SDL_Event *event);
void button_draw(void *component);
SDL_Texture* button_get_label_texture(Button *button);
SDL_Rect button_get_rect(Button *button);
void button_draw(void *component);

#endif // BUTTON_H

#include "../debug.h"
#include "element.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  TTF_Font *font;
  char *text;
  SDL_Color color;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  Element *element;
} Text;

void text_set_text(Text *text, const char *data);

Text *text_create(SDL_Renderer *renderer, const char *text,
                  const char *fontPath, int size) {
  Text *txt = malloc(sizeof(Text));
  txt->font = TTF_OpenFont(fontPath, size);
  if (!txt->font) {
    ERR("%s\n", TTF_GetError());
    assert(txt->font);
  }
  txt->color = (SDL_Color){0, 0, 0, 0};
  txt->element = element_create((SDL_Rect){0, 0, 0, 0});
  txt->renderer = renderer;
  text_set_text(txt, text);
  return txt;
}

void text_draw(Text *text) {
  if (!text->renderer || !text->texture)
    return;
  SDL_Rect rect = element_get_rect(text->element);
  SDL_RenderCopy(text->renderer, text->texture, NULL, &rect);
}

void text_destroy(Text *text) {
  if (text->font)
    TTF_CloseFont(text->font);
  if (text->texture)
    SDL_DestroyTexture(text->texture);
  free(text);
}

void text_update(Text *text) {
  SDL_Surface *surface =
      TTF_RenderText_Solid(text->font, text->text, text->color);
  text->texture = SDL_CreateTextureFromSurface(text->renderer, surface);
  SDL_Rect prev = element_get_rect(text->element);
  element_set_rect(text->element,
                   (SDL_Rect){prev.x, prev.y, surface->w, surface->h});
}

void text_set_text(Text *text, const char *data) {
  text->text = data;
  text_update(text);
}

void text_set_size(Text *text, int size) {
  TTF_SetFontSize(text->font, size);
  text_update(text);
}

void text_set_coordinate(Text *text, SDL_Point coordinate) {
  element_set_coordinate(text->element, coordinate);
}

void text_set_color(Text *text, SDL_Color color) {
  text->color = color;
  text_update(text);
}

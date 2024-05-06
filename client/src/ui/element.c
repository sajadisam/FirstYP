
#include <SDL2/SDL_rect.h>

typedef struct {
  SDL_Rect rect;
} Element;

Element *element_create(SDL_Rect rect) {
  Element *element = malloc(sizeof(Element));
  element->rect = rect;
  return element;
}

void element_destroy(Element *element) { free(element); }

void element_draw(Element *element) {}

void element_set_rect(Element *element, SDL_Rect rect) { element->rect = rect; }
void element_set_coordinate(Element *element, SDL_Point rect) {
  element->rect.x = rect.x;
  element->rect.y = rect.y;
}
SDL_Rect element_get_rect(Element *element) { return element->rect; }

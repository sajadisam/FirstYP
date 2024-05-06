#ifndef _Element_
#define _Element_

#include <SDL2/SDL_rect.h>

typedef struct Element Element;

Element *element_create(SDL_Rect rect, void (*draw)(void *component),
                        void *component);

void element_destroy(Element *element);

void element_draw(Element *element);

SDL_Rect element_get_rect(Element *element);
void element_set_rect(Element *element, SDL_Rect rect);
void element_set_coordinate(Element *element, SDL_Point rect);
void *element_get_coomponent(Element *element);

#endif // !_Element_

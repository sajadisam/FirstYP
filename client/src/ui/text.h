#ifndef _UI_
#define _UI_

#include <SDL2/SDL_render.h>

typedef struct Text Text;

Text *text_create(SDL_Renderer *renderer, const char *text,
                  const char *fontPath, int size);
void text_destroy(Text *text);

void text_draw(Text *text);
void text_set_text(Text *text, const char *data);

void text_set_size(Text *text, int size);
void text_set_coordinate(Text *text, SDL_Point coordinate);
void text_set_color(Text *text, SDL_Color color);

#endif // !_UI_

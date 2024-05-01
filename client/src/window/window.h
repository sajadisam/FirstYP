#ifndef _WINDOW_
#define _WINDOW_

#include <SDL2/SDL_render.h>

typedef struct window Window;

Window *window_create(const char *name, int width, int height);
void window_destroy(Window *window);
SDL_Texture *create_texture(Window *wnd, const char *path);

#endif // !_WINDOW_

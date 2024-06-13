#ifndef _MENU_
#define _MENU_
#include <SDL2/SDL.h>

typedef struct Menu Menu;

Menu *menu_create(SDL_Renderer *renderer);
void menu_destroy(Menu *menu);
void menu_render(Menu *menu, SDL_Renderer *renderer);
int menu_handle_event(Menu *menu, SDL_Event *event);
void initialize_img();
const char *menu_get_ip(Menu *menu);
const char *menu_get_port(Menu *menu);

#endif // _MENU_

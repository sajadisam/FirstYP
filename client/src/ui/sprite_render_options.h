#ifndef _SPRITE_RENDER_OPTIONS_
#define _SPRITE_RENDER_OPTIONS_
#include "../math/size.h"
#include "SDL2/SDL.h"

typedef struct {
  SDL_Point coordinate;
  Size size;
  SDL_Point crop;
  Size clip;
} SpriteRenderOptions;

#endif // !_SPRITE_RENDER_OPTIONS_

#ifndef _CANVAS_
#define _CANVAS_

#include "element.h"
#include "text.h"
typedef struct Canvas Canvas;

Canvas *canvas_create();

void canvas_destroy(Canvas *canvas);
void canvas_add_element(Canvas *canvas, Element *element);
void canvas_render(const Canvas *canvas);

#endif // !_CANVAS_

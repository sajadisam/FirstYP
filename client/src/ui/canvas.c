#include "../entity/entity_list.h"
#include "element.h"
#include "text.h"

typedef struct {
  EntityList *elements;
} Canvas;

Canvas *canvas_create() {
  Canvas *canvas = malloc(sizeof(Canvas));
  canvas->elements = entity_list_create(256, (void (*)(void *))element_destroy);
  return canvas;
}

void canvas_destroy(Canvas *canvas) {
  entity_list_destroy(canvas->elements);
  free(canvas);
}

void canvas_add_element(Canvas *canvas, Element *element) {
  entity_list_add(canvas->elements, element);
}

void canvas_render(const Canvas *canvas) {
  int size = entity_list_size(canvas->elements);
  for (int i = 0; i < size; i++) {
    Element *element = entity_list_get(canvas->elements, i);
    element_draw(element);
  }
}

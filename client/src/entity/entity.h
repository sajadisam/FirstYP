#ifndef ENTITY_H
#define ENTITY_H

typedef struct SDL_Point SDL_Point;
typedef struct Entity Entity;

Entity *entity_create();
void entity_destroy(Entity *entity);

void entity_move_coord(Entity *entity, float dx, float dy);

SDL_Point entity_get_coord(Entity const *entity);
void entity_set_coord(Entity *entity, SDL_Point coord);

#endif // ENTITY_H

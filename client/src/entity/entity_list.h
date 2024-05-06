#ifndef ENTITY_LIST_H
#define ENTITY_LIST_H

typedef struct EntityList EntityList;

EntityList *entity_list_create(int capacity,
                               void (*destroy_function)(void *entity));

void entity_list_destroy(EntityList *entityList);
int entity_list_indexof(EntityList *entityList, void *entity);
int entity_list_add(EntityList *entityList, void *entity);
void entity_list_remove(EntityList *entityList, void *entity);

void *entity_list_get(EntityList *entityList, int id);
int entity_list_size(EntityList *entityList);

#endif // ENTITY_LIST_H

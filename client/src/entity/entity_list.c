#include <assert.h>
#include <malloc.h>

typedef struct {
  void **storage;
  int size;
  int capacity;
  void (*destroy_function)(void *entity);
} EntityList;

EntityList *entity_list_create(int capacity,
                               void (*destroy_function)(void *entity)) {
  EntityList *entity_list = malloc(sizeof(EntityList));
  entity_list->storage = malloc(sizeof(void *) * capacity);
  entity_list->size = 0;
  entity_list->capacity = capacity;
  entity_list->destroy_function = destroy_function;
  return entity_list;
}

void entity_list_destroy(EntityList *entityList) {
  for (int i = 0; i < entityList->size; i++) {
    entityList->destroy_function(entityList->storage[i]);
  }
  free(entityList->storage);
  free(entityList);
}

int entity_list_indexof(EntityList *entityList, void *entity) {
  for (int i = 0; i < entityList->size; i++) {
    if (entityList->storage[i] == entity) {
      return i;
    }
  }
  return -1;
}

int entity_list_add(EntityList *entityList, void *entity) {
  assert(entityList->size < entityList->capacity);
  int id = entityList->size;
  entityList->storage[id] = entity;
  entityList->size++;
  return id;
}

void entity_list_remove(EntityList *entityList, void *entity) {
  int index = entity_list_indexof(entityList, entity);
  if (index == -1) {
    return;
  }
  for (int i = index; i < entityList->size - 1; i++) {
    entityList->storage[i] = entityList->storage[i + 1];
  }
  entityList->size--;
}

void *entity_list_get(EntityList *entityList, int id) {
  assert(id < entityList->size);
  return entityList->storage[id];
}

int entity_list_size(EntityList *entityList) { return entityList->size; }

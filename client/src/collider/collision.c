#include "../entity/entity_list.h"
#include "../world/world.h"
#include "collider.h"
#include <stdlib.h>

typedef struct {
  EntityList *colliders;
} Collision;

Collision *collision_create() {
  Collision *collision = malloc(sizeof(Collision));
  collision->colliders =
      entity_list_create(200, (void(*))(void *)collider_destroy);
  return collision;
}

void collision_destroy(Collision *collision) {
  entity_list_destroy(collision->colliders);
}

void collision_update(World *world, Collision *collision) {
  int len = entity_list_size(collision->colliders);
  for (int i = 0; i < len; i++) {
    Collider *a = entity_list_get(collision->colliders, i);
    for (int x = 0; x < len; x++) {
      if (x == i)
        continue;
      Collider *b = entity_list_get(collision->colliders, x);
      if (collider_execute(a, b)) {
        world_on_collision(world, a, b);
      }
    }
  }
}

void collision_add_collider(Collision *collision, Collider *collider) {
  entity_list_add(collision->colliders, collider);
}

void collision_remove_collider(Collision *collision, Collider *collider) {
  entity_list_remove(collision->colliders, collider);
}

#ifndef _COLLISION_
#define _COLLISION_

#include "collider.h"
typedef struct Collision Collision;

Collision *collision_create();
void collision_destroy(Collision *collision);
void collision_update(void *world, Collision *collision);
void collision_add_collider(Collision *collision, Collider *collider);
void collision_remove_collider(Collision *collision, Collider *collider);

#endif // !_COLLISION_

#ifndef _COLLIDER_COMMON_
#define _COLLIDER_COMMON_

typedef void (*OnCollisionFunc)(void *colliderA, void *colliderB);

typedef enum {
  COLLIDER_PLAYER,
  COLLIDER_PROJECTILE,
} ColliderType;

#endif // !_COLLIDER_COMMON_

#ifndef WORLD_H
#define WORLD_H

#include "../collider/collider.h"
#include "../entity/entity_list.h"
#include "../entity/mob.h"
#include "../entity/player.h"
#include "../projectile/projectile.h"
#include "level.h"

typedef struct World World;

World *world_create(SDL_Renderer *renderer);

void world_destroy(World *world);

void world_load_level(World *world, char const *tilesetName,
                      char const *levelName);

Level *world_get_level(World *world);

int world_add_player(World *world, void *player);
Player *world_get_player(World *world, size_t index);
Player *world_get_player_from_id(World *world, int id);
int world_add_mob(World *world, void *mob);
void world_remove_player(World *world, Player *player);
void world_add_collider(World *world, Collider *collider);
void world_remove_collider(World *world, Collider *collider);
void world_on_collision(World *world, Collider *a, Collider *b);

Mob *world_get_mob(World *world, size_t id);
Player *world_get_self_player(World *world);
EntityList *world_get_player_list(World *world);
EntityList *world_get_mob_list(World *world);
void world_update(World *world, float dt);
void world_render(World *world, SDL_Point pivot);
EntityList *world_get_projectiles_list(World *world);

void world_add_projectile(World *world, Projectile *projectile);
void world_remove_projectile(World *world, Projectile *projectile);

#endif // WORLD_H

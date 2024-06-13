#include "../collider/collider.h"
#include "../collider/collision.h"
#include "../entity/entity_list.h"
#include "../entity/mob.h"
#include "../entity/player.h"
#include "../projectile/projectile.h"
#include "SDL2/SDL_render.h"
#include "level.h"
#include "world_renderer.h"
#include <malloc.h>
#include <stdio.h>

typedef struct {
  Player *self;
  EntityList *player_list;
  EntityList *mob_list;
  EntityList *projectiles;
  Level *level;
  WorldRenderer *renderer;
  Collision *collision;
} World;

World *world_create(SDL_Renderer *renderer) {
  World *world = malloc(sizeof(World));
  world->player_list = entity_list_create(32, (void (*)(void *))player_destroy);
  world->self = player_create();
  world->mob_list = entity_list_create(32, (void (*)(void *))mob_destroy);
  world->collision = collision_create();
  world->projectiles =
      entity_list_create(2048, (void (*)(void *))projectile_destroy);
  world->level = NULL;
  world->renderer = world_renderer_create(renderer);
  collision_add_collider(world->collision, player_get_collider(world->self));
  return world; 
}

void world_destroy(World *world) {
  world_renderer_destroy(world->renderer);
  collision_destroy(world->collision);
  entity_list_destroy(world->player_list);
  entity_list_destroy(world->mob_list);
  level_destroy(world->level);
  free(world);
}

void world_load_level(World *world, char const *tilesetName,
                      char const *levelName) {
  if (world->level) {
    level_destroy(world->level);
    world->level = NULL;
  }
  char levelPath[256];
  char tilesetPath[256];
  for (int i = 0; i < 256; i++) {
    levelPath[i] = 0;
    tilesetPath[i] = 0;
  }
  sprintf(levelPath, "assets/levels/%s.csv", levelName);
  sprintf(tilesetPath, "assets/tilesets/%s.png", tilesetName);
  world->level = level_create(world_renderer_get_renderer(world->renderer),
                              tilesetPath, levelPath);
}

void world_remove_projectile(World *world, Projectile *projectile) {
  entity_list_remove(world->projectiles, projectile);
}

void world_projectile_update(World *world, float dt) {
  int projectile_count = entity_list_size(world->projectiles);
  for (int i = 0; i < projectile_count; i++) {
    Projectile *projectile = entity_list_get(world->projectiles, i);
    if (!projectile)
      continue;
    projectile_update(projectile, dt);
    SDL_Point start = projectile_get_start_coordinate(projectile);
    SDL_Point coord = projectile_get_coord(projectile);
    int deltaX = coord.x - start.x;
    int deltaY = coord.y - start.y;
    if ((deltaX > 500 || deltaX < -500) || (deltaY > 500 || deltaY < -500)) {
      world_remove_projectile(world, projectile);
      projectile_count--;
    }
  }
}

void world_update(World *world, float dt) {
  int player_count = entity_list_size(world->player_list);
  for (int i = 0; i < player_count; i++) {
    Player *player = entity_list_get(world->player_list, i);
    player_update(player, dt);
  }
  player_move_on_flags(world->self, dt);
  player_update(world->self, dt);
  world_projectile_update(world, dt);
  collision_update(world, world->collision);
}

void world_add_projectile(World *world, Projectile *projectile) {
  entity_list_add(world->projectiles, projectile);
}

void world_add_collider(World *world, Collider *collider) {
  collision_add_collider(world->collision, collider);
}

void world_remove_collider(World *world, Collider *collider) {
  collision_remove_collider(world->collision, collider);
}

void world_render(World *world, SDL_Point pivot) {
  world_renderer_render(world->renderer, world, pivot);
}

Level *world_get_level(World *world) { return world->level; }

int world_add_player(World *world, void *player) {
  world_add_collider(world, player_get_collider(player));
  return entity_list_add(world->player_list, player);
}

Player *world_get_player(World *world, int index) {
  return entity_list_get(world->player_list, index);
}

Player *world_get_player_from_id(World *world, int id) {
  for (int i = 0; i < entity_list_size(world->player_list); i++) {
    Player *player = entity_list_get(world->player_list, i);
    if (player_get_id(player) == id) {
      return player;
    }
  }
  return NULL;
}

void world_remove_player(World *world, Player *player) {
  world_remove_collider(world, player_get_collider(player));
  entity_list_remove(world->player_list, player);
}

Player *world_get_self_player(World *world) { return world->self; }

int world_add_mob(World *world, void *mob) {
  return entity_list_add(world->mob_list, mob);
}

void world_on_collision(World *world, Collider *a, Collider *b) {
  if (!a || !b)
    return;
  ColliderType typeA = collider_get_type(a);
  ColliderType typeB = collider_get_type(b);
  if (typeA == COLLIDER_PLAYER && typeB == COLLIDER_PROJECTILE) {
    Projectile *projectile = collider_get_target(b);
    Player *player = collider_get_target(a);
    player_decrement_health(player, 17);
    world_remove_projectile(world, projectile);
    world_remove_collider(world, b);
  }
  if (typeB == COLLIDER_PLAYER && typeA == COLLIDER_PROJECTILE) {
    Projectile *projectile = collider_get_target(a);
    Player *player = collider_get_target(b);
    player_decrement_health(player, 17);
    world_remove_projectile(world, projectile);
    world_remove_collider(world, a);
  }
}
Player *world_get_mob(World *world, int id) {
  return entity_list_get(world->mob_list, id);
}

EntityList *world_get_player_list(World *world) { return world->player_list; }
EntityList *world_get_projectiles_list(World *world) {
  return world->projectiles;
}

EntityList *world_get_mob_list(World *world) { return world->mob_list; }

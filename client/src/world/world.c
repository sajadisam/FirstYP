#include "../entity/entity_list.h"
#include "../entity/mob.h"
#include "../entity/player.h"
#include "SDL2/SDL_render.h"
#include "level.h"
#include "world_renderer.h"
#include <malloc.h>
#include <stdio.h>

typedef struct {
  Player *self;
  EntityList *player_list;
  EntityList *mob_list;
  Level *level;
  WorldRenderer *renderer;
} World;

World *world_create(SDL_Renderer *renderer) {
  World *world = malloc(sizeof(World));
  world->player_list = entity_list_create(32, (void (*)(void *))player_destroy);
  world->self = player_create();
  world->mob_list = entity_list_create(32, (void (*)(void *))mob_destroy);
  world->level = NULL;
  world->renderer = world_renderer_create(renderer);
  return world;
}

void world_destroy(World *world) {
  world_renderer_destroy(world->renderer);
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

void world_update(World *world, float dt) {
  int player_count = entity_list_size(world->player_list);
  for (int i = 0; i < player_count; i++) {
    Player *player = entity_list_get(world->player_list, i);
    player_update(player, dt);
  }
  player_update(world->self, dt);
}

void world_render(World *world, SDL_Point pivot) {
  world_renderer_render(world->renderer, world, pivot);
}

Level *world_get_level(World *world) { return world->level; }

int world_add_player(World *world, void *player) {
  return entity_list_add(world->player_list, player);
}

Player *world_get_player(World *world, int id) {
  return entity_list_get(world->player_list, id);
}

Player *world_get_self_player(World *world) { return world->self; }

int world_add_mob(World *world, void *mob) {
  return entity_list_add(world->mob_list, mob);
}

Player *world_get_mob(World *world, int id) {
  return entity_list_get(world->mob_list, id);
}

EntityList *world_get_player_list(World *world) { return world->player_list; }

EntityList *world_get_mob_list(World *world) { return world->mob_list; }

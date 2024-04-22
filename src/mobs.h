// mob.h
#ifndef MOB_H
#define MOB_H

#include <stdbool.h>
#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect position;
    int health;
    int speed;
    // Add more properties as needed
} Mob;

typedef struct MobNode {
    Mob mob;
    struct MobNode *next;
} MobNode;

/*
void InitMob(Mob *mob, int x, int y, int w, int h, int health, int speed);
void UpdateMob(Mob *mob, SDL_Point playerPos);
void RenderMob(SDL_Renderer *renderer, SDL_Texture *mobTexture, Mob *mob);
*/

//bool CheckMobCollision(Mob *mob, SDL_Rect other);
void TrySpawnMob();
void UpdateAndRenderMobs(SDL_Renderer *renderer, SDL_Texture *mobTexture, SDL_Point playerPos);
void RemoveMob(MobNode **mobNode);
void AddMob(int x, int y, int w, int h, int health, int speed);
bool CheckCollision(SDL_Rect a, SDL_Rect b);
void CheckMobsCollision(SDL_Rect playerRect);

#endif // MOB_H

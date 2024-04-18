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

void InitMob(Mob *mob, int x, int y, int w, int h, int health, int speed);
void UpdateMob(Mob *mob, SDL_Point playerPos);
void RenderMob(SDL_Renderer *renderer, SDL_Texture *mobTexture, Mob *mob);
bool CheckMobCollision(Mob *mob, SDL_Rect other);

#endif // MOB_H

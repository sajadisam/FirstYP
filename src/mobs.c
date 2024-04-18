// mob.c
#include "mobs.h"
#include <stdbool.h>

void InitMob(Mob *mob, int x, int y, int w, int h, int health, int speed) {
    mob->position = (SDL_Rect){x, y, w, h};
    mob->health = health;
    mob->speed = speed;
}

void UpdateMob(Mob *mob, SDL_Point playerPos) {
    // Calculate deltas
    int deltaX = playerPos.x - mob->position.x;
    int deltaY = playerPos.y - mob->position.y;
    if (deltaX != 0) {
      mob->position.x += (deltaX > 0 ? mob->speed : -mob->speed);
    }

    if (deltaY != 0) {
      mob->position.y += (deltaY > 0 ? mob->speed : -mob->speed);
    }

    // Calculate distance
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);

    if (distance > 1) {  // Avoid division by zero
        // Normalize the direction vector
        float dirX = deltaX / distance;
        float dirY = deltaY / distance;

        // Update mob position based on normalized direction vector and speed
        mob->position.x += dirX * mob->speed;
        mob->position.y += dirY * mob->speed;
        printf("deltaX: %d, deltaY: %d, dirX: %f, dirY: %f, distance: %f\n",
       deltaX, deltaY, dirX, dirY, distance);
    }
}

void RenderMob(SDL_Renderer *renderer, SDL_Texture *mobTexture, Mob *mob) {
    SDL_RenderCopy(renderer, mobTexture, NULL, &mob->position);
}

bool CheckMobCollision(Mob *mob, SDL_Rect other) {
    return (mob->position.x + mob->position.w > other.x) &&
           (mob->position.x < other.x + other.w) &&
           (mob->position.y + mob->position.h > other.y) &&
           (mob->position.y < other.y + other.h);
}
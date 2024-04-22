// mob.c
#include "mobs.h"
#include "config.h"
#include <stdbool.h>
#include <math.h>


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
/*
bool CheckMobCollision(Mob *mob, SDL_Rect other) {
    return (mob->position.x + mob->position.w > other.x) &&
           (mob->position.x < other.x + other.w) &&
           (mob->position.y + mob->position.h > other.y) &&
           (mob->position.y < other.y + other.h);
}
*/

MobNode *mobList = NULL;

void AddMob(int x, int y, int w, int h, int health, int speed) {
    MobNode *newMob = malloc(sizeof(MobNode));
    if (newMob == NULL) return; // Handle malloc failure

    InitMob(&newMob->mob, x, y, w, h, health, speed);
    newMob->next = mobList;
    mobList = newMob;
}

void RemoveMob(MobNode **mobNode) {
    MobNode *temp = *mobNode;
    *mobNode = (*mobNode)->next;
    free(temp);
}

void UpdateAndRenderMobs(SDL_Renderer *renderer, SDL_Texture *mobTexture, SDL_Point playerPos) {
    MobNode **current = &mobList;
    while (*current != NULL) {
        UpdateMob(&(*current)->mob, playerPos);

        if ((*current)->mob.health <= 0) {
            RemoveMob(current);
        } else {
            RenderMob(renderer, mobTexture, &(*current)->mob);
            current = &(*current)->next;
        }
    }
}

void TrySpawnMob() {
    if (rand() % 75 == 0) {  // Approximately 1 in 75 chance each frame
        int x = rand() % 640;
        int y = rand() % 480;
        AddMob(x, y, 50, 50, 100, 2);
    }
}

bool CheckCollision(SDL_Rect a, SDL_Rect b) {
    return (a.x + a.w > b.x) &&
           (a.x < b.x + b.w) &&
           (a.y + a.h > b.y) &&
           (a.y < b.y + b.h);
}

void CheckMobsCollision(SDL_Rect playerRect) {
    MobNode *current = mobList;
    while (current != NULL) {
        if (CheckCollision(current->mob.position, playerRect)) {
            // Collision detected
            // You can handle it here, e.g., reducing mob health or player health
            //current->mob.health -= 10; // Example of reducing mob's health
            if (current->mob.health <= 0) {
                // If mob's health is 0 or less, remove it from the list
                MobNode *toRemove = current;
                current = current->next;
                RemoveMob(&toRemove); // Pass the address of the node to be removed
                continue; // Skip the rest of the loop
            }
        }
        current = current->next;
    }
}
#include "config.h"
#include "player.h"
#include "mobs.h"
#include "window.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FPS 60
#define ARROW_SPEED 200
#define MAX_ARROWS 10
#define ARROW_SPEED 200

typedef struct {
  SDL_Rect arrowRect;
  SDL_Rect arrowPosition;
  float velocityX;
  float velocityY;
  bool active;
  SDL_RendererFlip flip;
} Arrow;

typedef struct {
  int health;
  int arrowsRemaining;
} GameStatus;

GameStatus gameStatus = {100, MAX_ARROWS}; // Example initial values

bool CheckCollision(SDL_Rect a, SDL_Rect b) {
  return (a.x + a.w > b.x) && (a.x < b.x + b.w) && (a.y + a.h > b.y) &&
         (a.y < b.y + b.h);
}

void drawUI(SDL_Renderer *renderer, TTF_Font *font, GameStatus *gameStatus) {
  char info[256];
  SDL_Color textColor1 = {255, 255, 255, 255}; // white color
  SDL_Color textColor2 = {255, 0, 0, 255};
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Rect rect;
  // ritar mängden pilar
  sprintf(info, "Arrows: %d", gameStatus->arrowsRemaining);
  surface = TTF_RenderText_Solid(font, info, textColor1);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  rect = (SDL_Rect){10, 10, surface->w,
                    surface->h}; // koordinater för top-right corner
  SDL_RenderCopy(renderer, texture, NULL, &rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
  // ritar player-hp
  sprintf(info, "Health: %d", gameStatus->health);
  surface = TTF_RenderText_Solid(font, info, textColor2);
  texture = SDL_CreateTextureFromSurface(renderer, surface);
  rect.y += surface->h;
  rect.x = 10; // Reset the x coordinate
  rect.w = surface->w;
  rect.h = surface->h;
  SDL_RenderCopy(renderer, texture, NULL, &rect);
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void initArrows(Arrow *arrows, GameStatus *gameStatus, int amountArrows) {
  for (int i = 0; i < MAX_ARROWS; i++) {
    arrows[i].active = false;
  }
  amountArrows = 20;
  gameStatus->arrowsRemaining = amountArrows;
}

void shootArrow(int playerX, int playerY, int direction, Arrow *arrows, int height, int width) {
  int frameWidth, frameHeight;
  int column = 0;
  frameWidth = width / 2;
  frameHeight = height;

  for (int i = 0; i < MAX_ARROWS; i++) {
    if (!arrows[i].active) {
      arrows[i].arrowPosition.x = arrows[i].arrowPosition.y = 0;
      arrows[i].arrowPosition.w = arrows[i].arrowPosition.h = 2;

      arrows[i].arrowPosition.x = playerX / 1.04;
      arrows[i].arrowPosition.y = playerY / 1.04;
      arrows[i].arrowPosition.w = frameWidth / 6;
      arrows[i].arrowPosition.h = frameHeight / 6;

      arrows[i].arrowRect.x = 0;
      arrows[i].arrowRect.y = 0;
      arrows[i].arrowRect.w = frameWidth;
      arrows[i].arrowRect.h = frameHeight;
      arrows[i].flip = SDL_FLIP_NONE;
      switch (direction) {
      case 0: // Down
        column = 0;
        arrows[i].arrowRect.x = column * frameWidth;
        arrows[i].flip = SDL_FLIP_VERTICAL;
        arrows[i].velocityX = 0;
        arrows[i].velocityY = ARROW_SPEED;
        break;
      case 1: // Left
        column = 1;
        arrows[i].arrowRect.x = column * frameWidth;
        arrows[i].flip = SDL_FLIP_HORIZONTAL;
        arrows[i].velocityX = -ARROW_SPEED;
        arrows[i].velocityY = 0;
        column = 0;
        break;
      case 2: // Right
        column = 1;
        arrows[i].arrowRect.x = column * frameWidth;
        arrows[i].velocityX = ARROW_SPEED;
        arrows[i].velocityY = 0;
        break;
      case 3: // Up
        column = 0;
        arrows[i].arrowRect.x = column * frameWidth;
        arrows[i].velocityX = 0;
        arrows[i].velocityY = -ARROW_SPEED;
        break;
      }
      arrows[i].active = true;
      break; // Exit after activating an arrow
    }
  }
}

void updateArrows(Arrow *arrows, float deltaTime) {
  for (int i = 0; i < MAX_ARROWS; i++) {
    if (arrows[i].active) {
      arrows[i].arrowPosition.x += arrows[i].velocityX * deltaTime * 2;
      arrows[i].arrowPosition.y += arrows[i].velocityY * deltaTime * 2;

      // Check if the arrow is off-screen, then deactivate
      if (arrows[i].arrowPosition.x < 0 ||
          arrows[i].arrowPosition.x > WINDOW_WIDTH ||
          arrows[i].arrowPosition.y < 0 ||
          arrows[i].arrowPosition.y > WINDOW_HEIGHT) {
        arrows[i].active = false;
      }
    }
  }
}

int main(int argv, char **args) {
  float arrowLossTimer = 0;
  Arrow arrows[MAX_ARROWS];
  float arrowShootTimer = 0;
  float arrowShootInterval = 2.0;
  srand(time(NULL));
  bool newImageVisible = true;
///////////
  Mob mob;  // Declare your mob variable
  InitMob(&mob, rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, 50, 50, 100, 1);  // Initialize the mob
//////////
  if (TTF_Init() != 0) {
    printf("Error initializing SDL_ttf: %s\n", TTF_GetError());
    SDL_Quit();
    return 1;
  }

  if (Window_IntitializeSDL())
    return 1;

  Window *wnd = Window_Create("Spel", WINDOW_WIDTH, WINDOW_HEIGHT);
  if (!wnd)
    return 2;

  SDL_Texture *pTexture = Window_Texture("./resources/player.png", wnd);
  SDL_Texture *newTexture = Window_Texture("./resources/redGem.png", wnd);
  SDL_Texture *mapTexture = Window_Texture("./resources/Map.png", wnd);
  SDL_Texture *arrowTexture = Window_Texture("./resources/arrow.png", wnd);
  SDL_Texture *mobTexture = Window_Texture("./resources/mob.png", wnd);

  initArrows(arrows, &gameStatus, 30);
  Uint32 startTick = SDL_GetTicks(), endTick;
  float deltaTime;

  int textureWidth, textureHeight, frameWidth, frameHeight, arrowWidth,
      arrowHeight;
  int frameTime = 0;
  int newX = rand() % WINDOW_WIDTH;
  int newY = rand() % WINDOW_HEIGHT;
  SDL_Rect newImagePosition = {newX, newY, 50, 50};
  SDL_Rect mapRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

  SDL_QueryTexture(pTexture, NULL, NULL, &textureWidth, &textureHeight);
  SDL_QueryTexture(arrowTexture, NULL, NULL, &arrowWidth, &arrowHeight);
  frameWidth = textureWidth / 3;
  frameHeight = textureHeight / 4;

  int frame = 0;
  bool running = true;

  bool closeWindow = false;
  SDL_Event event;
  TTF_Font *font = TTF_OpenFont("./resources/Sans.ttf", 24);
  if (!font) {
    printf("Failed to load : %s\n", TTF_GetError());
  }

  bool isFullscreen = false;
  Player player;
  player.movement_flags = (PlayerMovementFlags){};
  player.coordinate = (SDL_Point){
      (WINDOW_WIDTH - frameWidth) / 2,
      (WINDOW_HEIGHT - frameHeight) / 2,
  };

  player.frame_size = (Vec2){
      frameWidth,
      frameHeight,
  };
  player.speed = 5;

  while (!closeWindow) {
    SDL_Rect nextPlayerFrame;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        closeWindow = true;
        break;
      }
      PlayerEvents(&event, &player, &nextPlayerFrame);
    }

    frameTime++;
    if (frameTime == 5) {
      frameTime = 0;
      nextPlayerFrame.x += frameWidth;
      if (nextPlayerFrame.x >= textureWidth)
        nextPlayerFrame.x = 0;
    }
/////////
    UpdateMob(&mob, player.coordinate);  // Update the mob's position based on the player's position
    RenderMob(wnd->m_Renderer, mobTexture, &mob);  // Render the mob

    if (CheckMobCollision(&mob, GetPlayerBoundingBox(&player))) {
      gameStatus.health -= 10;  
      if (gameStatus.health <= 0) {
        gameStatus.health = 100;
      }
    }
/////////

    endTick = SDL_GetTicks();
    deltaTime =
        (endTick - startTick) / 1000.0f; // Convert milliseconds to seconds
    startTick = endTick;
    printf("deltaTime: %f, arrowLossTimer: %f\n", deltaTime, arrowLossTimer);

    arrowLossTimer += deltaTime;
    if (arrowLossTimer >= 1.0f) {
      if (gameStatus.arrowsRemaining > 0) {
        gameStatus.arrowsRemaining--;
      }
      arrowLossTimer = 0;
    }

    drawUI(wnd->m_Renderer, font, &gameStatus);
    SDL_RenderPresent(wnd->m_Renderer);

    PlayerEventLoop(&player);

    updateArrows(arrows, deltaTime);
    arrowShootTimer -= deltaTime;
    if (arrowShootTimer <= 0) {
      shootArrow(player.coordinate.x, player.coordinate.y,
                 nextPlayerFrame.y / player.frame_size.h, arrows, arrowHeight,
                 arrowWidth);               // Shoot an arrow
      arrowShootTimer = arrowShootInterval; // Reset the timer
    }

    SDL_RenderClear(wnd->m_Renderer);
    SDL_RenderCopy(wnd->m_Renderer, mapTexture, NULL, &mapRect);
    SDL_RenderCopy(wnd->m_Renderer, pTexture,
                   &(SDL_Rect){
                       nextPlayerFrame.x,
                       nextPlayerFrame.y,
                       player.frame_size.w,
                       player.frame_size.h,
                   },
                   (SDL_Rect *)&player.coordinate);

    for (int i = 0; i < MAX_ARROWS; i++) {
      if (arrows[i].active) {
        printf("Arrow %d: Active %d, Position (%f, %f)\n", i, arrows[i].active,
               arrows[i].arrowPosition.x, arrows[i].arrowPosition.y);
        SDL_RenderCopyEx(wnd->m_Renderer, arrowTexture, &arrows[i].arrowRect,
                         &arrows[i].arrowPosition, 0, NULL, arrows[i].flip);
      }
    }

    if (newImageVisible) {
      SDL_RenderCopy(wnd->m_Renderer, newTexture, NULL, &newImagePosition);
    }

    if (CheckCollision(GetPlayerBoundingBox(&player), newImagePosition) &&
        newImageVisible) {
      newImageVisible = false;
      player.speed *= 2;
    }
  }

  TTF_CloseFont(font);
  TTF_Quit();
  Window_Destroy(wnd);
  SDL_Quit();
  return 0;
}

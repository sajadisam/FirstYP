#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 400
#define FRAME_DELAY_MS 100
#define FPS 60

bool CheckCollision(SDL_Rect a, SDL_Rect b) {
  return (a.x + a.w > b.x) && (a.x < b.x + b.w) && (a.y + a.h > b.y) &&
         (a.y < b.y + b.h);
}

// From Ishar
int main(int argv, char **args) {
  int SPEED = 100;
  int mobSPEED = 1;
  srand(time(NULL));
  bool newImageVisible = true;
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    printf("Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Window *pWindow =
      SDL_CreateWindow("Enkelt exempel 1", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!pWindow) {
    printf("Error: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }
  SDL_Renderer *pRenderer = SDL_CreateRenderer(
      pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!pRenderer) {
    printf("Error: %s\n", SDL_GetError());
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 1;
  }

  SDL_Surface *pSurface = IMG_Load("./resources/player.png");
  if (!pSurface) {
    printf("Error: %s\n", SDL_GetError());
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 1;
  }
  SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
  SDL_FreeSurface(pSurface);
  if (!pTexture) {
    printf("Error: %s\n", SDL_GetError());
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 1;
  }

  SDL_Surface *newSurface = IMG_Load("./resources/redGem.png");
  if (!newSurface) {
    printf("Unable to load image %s! SDL_image Error: %s\n",
           "resources/ship.png", IMG_GetError());
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 1;
  }

  SDL_Texture *newTexture = SDL_CreateTextureFromSurface(pRenderer, newSurface);
  SDL_FreeSurface(newSurface);
  if (!newTexture) {
    printf("Unable to create texture from %s! SDL Error: %s\n",
           "resources/ship.png", SDL_GetError());
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 1;
  }

  SDL_Surface *mapSurface = IMG_Load("./resources/Map.png");
  if (!mapSurface) {
    printf("Unable to load image %s! SDL_image Error: %s\n",
           "resources/map.png", IMG_GetError());
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 1;
  }

  SDL_Texture *mapTexture = SDL_CreateTextureFromSurface(pRenderer, mapSurface);
  SDL_FreeSurface(mapSurface);
  if (!mapTexture) {
    printf("Unable to create texture from %s! SDL Error: %s\n",
           "resources/ship.png", SDL_GetError());
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 1;
  }

  SDL_Surface *mobSurface = IMG_Load("./resources/mob.png");
  if (!mobSurface) {
    printf("Error: %s\n", SDL_GetError());
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 1;
  }
  SDL_Texture *mobTexture = SDL_CreateTextureFromSurface(pRenderer, mobSurface);
  SDL_FreeSurface(mobSurface);
  if (!mobTexture) {
    printf("Error: %s\n", SDL_GetError());
    SDL_DestroyRenderer(pRenderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 1;
  }

  int textureWidth, textureHeight, frameWidth, frameHeight;
  int frameTime = 0;
  int mobFrameTime = 0;
  int newX = rand() % WINDOW_WIDTH;
  int newY = rand() % WINDOW_HEIGHT;
  SDL_Rect playerRect;
  SDL_Rect playerPosition;
  SDL_Rect newImagePosition = {newX, newY, 50, 50};
  SDL_Rect mapRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_Rect mobRect;
  SDL_Rect mobPosition = {rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT, 50, 50};

  playerPosition.x = playerPosition.y = 0;
  playerPosition.w = playerPosition.h = 12;

  SDL_QueryTexture(pTexture, NULL, NULL, &textureWidth, &textureHeight);
  SDL_QueryTexture(mobTexture, NULL, NULL, &textureWidth, &textureHeight);

  frameWidth = textureWidth / 3;
  frameHeight = textureHeight / 4;

  playerRect.x = playerRect.y = 0;
  playerRect.w = frameWidth;
  playerRect.h = frameHeight;

  mobRect.x = mobRect.y = 0;
  mobRect.w = frameWidth;
  mobRect.h = frameHeight;


  int frame = 0;
  bool running = true;

  playerPosition.x = (WINDOW_WIDTH - frameWidth) / 2;   // left side
  playerPosition.y = (WINDOW_HEIGHT - frameHeight) / 2; // upper side
  playerPosition.w = frameWidth;
  playerPosition.h = frameHeight;
  float playerVelocityX = 0; 
  float playerVelocityY = 0;

  bool closeWindow = false;
  bool up, down, left, right;
  up = down = left = right = false;
  int currentRow = 0;
  SDL_Event event;

  while (!closeWindow) {

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
      case SDL_QUIT:
        closeWindow = true;
        break;
      case SDL_KEYDOWN:
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
          up = true;
          currentRow = 3; // Set to the second row for the left movement
          playerRect.y = currentRow * frameHeight;
          break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
          left = true;
          currentRow = 1; // Set to the second row for the left movement
          playerRect.y = currentRow * frameHeight;
          break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
          down = true;
          currentRow = 0; // Set to the second row for the left movement
          playerRect.y = currentRow * frameHeight;
          break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
          right = true;
          currentRow = 2; // Set to the second row for the left movement
          playerRect.y = currentRow * frameHeight;
          break;
        }
        break;
      case SDL_KEYUP:
        switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
          up = false;
          break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
          left = false;
          break;
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN: 
          down = false;
          break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
          right = false;
          break;
        }
        break;
      }
    }
    frameTime++;

    if (frameTime == 5) {
      frameTime = 0;
      playerRect.x += frameWidth;
      if (playerRect.x >= textureWidth)
        playerRect.x = 0;
    }

  mobFrameTime++;
  if (mobFrameTime >= (FPS / 2)) {
    mobFrameTime = 0;
    frame = (frame + 1) % 3; 
    mobRect.x = frame * frameWidth;
  }
    

    playerVelocityX = playerVelocityY = 0;
    if (up && !down)
      playerVelocityY = -SPEED;
    if (down && !up)
      playerVelocityY = SPEED;
    if (left && !right)
      playerVelocityX = -SPEED;
    if (right && !left)
      playerVelocityX = SPEED;
    playerPosition.x += playerVelocityX / 60; 
    playerPosition.y += playerVelocityY / 60;

    float newPlayerX = playerPosition.x + playerVelocityX / FPS;
    float newPlayerY = playerPosition.y + playerVelocityY / FPS;

    int deltaX = playerPosition.x - mobPosition.x;
    int deltaY = playerPosition.y - mobPosition.y;
    float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
    float dirX = deltaX / distance;
    float dirY = deltaY / distance;

    int mobCurrentRow = 0;

    if (distance > 1) { 
      dirX = deltaX / distance;
      dirY = deltaY / distance;
      mobPosition.x += dirX * mobSPEED;
      mobPosition.y += dirY * mobSPEED;
   
       if (fabs(dirX) > fabs(dirY)) {
            mobCurrentRow = (dirX > 0) ? 2 : 1; // Right or Left
        } else {
            mobCurrentRow = (dirY > 0) ? 0 : 3; // Down or Up
        }
        mobRect.y = mobCurrentRow * frameHeight;
    }
    
    if (newPlayerX < 0) {
      newPlayerX = 0; 
    } else if (newPlayerX + playerPosition.w > WINDOW_WIDTH) {
      newPlayerX = WINDOW_WIDTH - playerPosition.w; 
    }

    if (newPlayerY < 0) {
      newPlayerY = 0; 
    } else if (newPlayerY + playerPosition.h > WINDOW_HEIGHT) {
      newPlayerY = WINDOW_HEIGHT - playerPosition.h; 
    }

    playerPosition.x = newPlayerX;
    playerPosition.y = newPlayerY;

    SDL_RenderClear(pRenderer);
    SDL_RenderCopy(pRenderer, mapTexture, NULL, &mapRect);
    SDL_RenderCopy(pRenderer, mobTexture, &mobRect, &mobPosition);
    SDL_RenderCopy(pRenderer, pTexture, &playerRect, &playerPosition); 
    if (newImageVisible) {
      SDL_RenderCopy(pRenderer, newTexture, NULL, &newImagePosition);
    }
    if (CheckCollision(playerPosition, newImagePosition) && newImageVisible) {
      newImageVisible = false;
      SPEED *= 3;
    }
    SDL_RenderPresent(pRenderer);
    SDL_Delay(16);
  }

  SDL_DestroyTexture(pTexture);
  SDL_DestroyRenderer(pRenderer);
  SDL_DestroyWindow(pWindow);

  SDL_Quit();
  return 0;
}

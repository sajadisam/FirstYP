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

int main(int argv, char **args) {
  int SPEED = 100;
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

  /**/ SDL_Surface *pSurface = IMG_Load("./resources/hejsan.png");
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

  SDL_Surface *newSurface = IMG_Load("./resources/Ship.png");
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

  int textureWidth, textureHeight, frameWidth, frameHeight;
  int frameTime = 0;
  float newX = rand() % WINDOW_WIDTH;
  float newY = rand() % WINDOW_HEIGHT;
  SDL_Rect playerRect;
  SDL_Rect playerPosition;
  SDL_Rect newImagePosition = {newX, newY, 50, 50};

  playerPosition.x = playerPosition.y = 0;
  playerPosition.w = playerPosition.h = 12;

  SDL_QueryTexture(pTexture, NULL, NULL, &textureWidth, &textureHeight);

  // Assuming the sprite sheet has frames placed horizontally

  frameWidth = textureWidth / 3;
  frameHeight = textureHeight / 4;

  playerRect.x = playerRect.y = 0;
  playerRect.w = frameWidth;
  playerRect.h = frameHeight;

  int frame = 0;
  bool running = true;

  playerPosition.x = (WINDOW_WIDTH - frameWidth) / 2;   // left side
  playerPosition.y = (WINDOW_HEIGHT - frameHeight) / 2; // upper side
  playerPosition.w = frameWidth;
  playerPosition.h = frameHeight;
  float playerVelocityX = 0; // unit: pixels/s
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
        case SDL_SCANCODE_DOWN: //Hej
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

    playerVelocityX = playerVelocityY = 0;
    if (up && !down)
      playerVelocityY = -SPEED;
    if (down && !up)
      playerVelocityY = SPEED;
    if (left && !right)
      playerVelocityX = -SPEED;
    if (right && !left)
      playerVelocityX = SPEED;
    playerPosition.x += playerVelocityX / 60; // Adjust SPEED definition to be float for smooth movement
    playerPosition.y += playerVelocityY / 60;

    float newPlayerX = playerPosition.x + playerVelocityX / FPS;
    float newPlayerY = playerPosition.y + playerVelocityY / FPS;

    // Constrain the new position within the window's boundaries
    if (newPlayerX < 0) {
      newPlayerX = 0; // Left boundary
    } else if (newPlayerX + playerPosition.w > WINDOW_WIDTH) {
      newPlayerX = WINDOW_WIDTH - playerPosition.w; // Right boundary
    }

    if (newPlayerY < 0) {
      newPlayerY = 0; // Top boundary
    } else if (newPlayerY + playerPosition.h > WINDOW_HEIGHT) {
      newPlayerY = WINDOW_HEIGHT - playerPosition.h; // Bottom boundary
    }

    // Update player position
    playerPosition.x = newPlayerX;
    playerPosition.y = newPlayerY;

    SDL_RenderClear(pRenderer);
    SDL_RenderCopy(pRenderer, pTexture, &playerRect,
                   &playerPosition); // Render the current frame
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

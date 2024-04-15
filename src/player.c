#include "player.h"

void Player_Events(SDL_Event *event, Player *player) {
  // switch (event.type) {
  // case SDL_QUIT:
  //   closeWindow = true;
  //   break;
  // case SDL_KEYDOWN:
  //   switch (event.key.keysym.scancode) {
  //   case SDL_SCANCODE_W:
  //   case SDL_SCANCODE_UP:
  //     up = true;
  //     currentRow = 3; // Set to the second row for the left movement
  //     playerRect.y = currentRow * frameHeight;
  //     break;
  //   case SDL_SCANCODE_A:
  //   case SDL_SCANCODE_LEFT:
  //     left = true;
  //     currentRow = 1; // Set to the second row for the left movement
  //     playerRect.y = currentRow * frameHeight;
  //     break;
  //   case SDL_SCANCODE_S:
  //   case SDL_SCANCODE_DOWN:
  //     down = true;
  //     currentRow = 0; // Set to the second row for the left movement
  //     playerRect.y = currentRow * frameHeight;
  //     break;
  //   case SDL_SCANCODE_D:
  //   case SDL_SCANCODE_RIGHT:
  //     right = true;
  //     currentRow = 2; // Set to the second row for the left movement
  //     playerRect.y = currentRow * frameHeight;
  //     break;
  //   }
  //   break;
  // case SDL_KEYUP:
  //   switch (event.key.keysym.scancode) {
  //   case SDL_SCANCODE_W:
  //   case SDL_SCANCODE_UP:
  //     up = false;
  //     break;
  //   case SDL_SCANCODE_A:
  //   case SDL_SCANCODE_LEFT:
  //     left = false;
  //     break;
  //   case SDL_SCANCODE_S:
  //   case SDL_SCANCODE_DOWN:
  //     down = false;
  //     break;
  //   case SDL_SCANCODE_D:
  //   case SDL_SCANCODE_RIGHT:
  //     right = false;
  //     break;
  //   }
  //   break;
  // }
}

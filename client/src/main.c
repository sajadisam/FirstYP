#include "setup.h"

int main() {
  Game *game = initialize();
  run(game);
  shutdown(game);
}

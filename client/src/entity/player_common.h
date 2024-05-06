#ifndef PLAYER_FLAGS_H
#define PLAYER_FLAGS_H

typedef unsigned int PlayerFlag;

#define PLAYER_FLAG_NONE (0)
#define PLAYER_FLAG_MOVE_UP (1 << 0)
#define PLAYER_FLAG_MOVE_DOWN (1 << 1)
#define PLAYER_FLAG_MOVE_LEFT (1 << 2)
#define PLAYER_FLAG_MOVE_RIGHT (1 << 3)
#define PLAYER_FLAG_MOVE_HORIZONTAL                                            \
  (PLAYER_FLAG_MOVE_LEFT | PLAYER_FLAG_MOVE_RIGHT)
#define PLAYER_FLAG_MOVE_VERTICAL (PLAYER_FLAG_MOVE_DOWN | PLAYER_FLAG_MOVE_UP)
#define PLAYER_FLAG_MOVE_ANY                                                   \
  (PLAYER_FLAG_MOVE_DOWN | PLAYER_FLAG_MOVE_UP | PLAYER_FLAG_MOVE_LEFT |       \
   PLAYER_FLAG_MOVE_RIGHT)

#endif // PLAYER_FLAGS_H

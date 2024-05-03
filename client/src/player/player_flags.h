#ifndef _PlayerFlags_
#define _PlayerFlags_

typedef enum {
  IDLE = 0,
  MOVINGUP = 1,
  MOVINGDOWN = 2,
  MOVINGLEFT = 4,
  MOVINGRIGHT = 8,
} PlayerFlag;

#endif // !_PlayerFlags_

#include <malloc.h>

typedef struct {
  float speed;
  float timer;
  int base;
  int frame;
  int frame_count;
} Animation;

Animation *animation_create(float speed, int frame_count) {
  Animation *animation = malloc(sizeof(Animation));
  animation->speed = speed;
  animation->timer = 0.0f;
  animation->base = 0;
  animation->frame = 0;
  animation->frame_count = frame_count;
  return animation;
}

void animation_destroy(Animation *animation) { free(animation); }

void animation_reset(Animation *animation) {
  animation->timer = 0.0f;
  animation->frame = 0;
  animation->base = 0;
}

void animation_update(Animation *animation, float dt) {
  animation->timer += dt;
  if (animation->timer > animation->speed) {
    animation->timer = 0.0f;
    animation->frame = (animation->frame + 1) % animation->frame_count;
  }
}

void animation_set_base(Animation *animation, int base) {
  animation->base = base;
}

void animation_set_frame(Animation *animation, int frame) {
  animation->frame = frame;
  animation->timer = 0.0f;
}

int animation_get_frame(Animation const *animation) {
  return animation->base + animation->frame;
}

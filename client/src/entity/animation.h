#ifndef ANIMATION_H
#define ANIMATION_H

typedef struct Animation Animation;

Animation *animation_create(float speed, int frame_count);

void animation_destroy(Animation *animation);
void animation_reset(Animation *animation);
void animation_update(Animation *animation, float dt);

void animation_set_base(Animation *animation, int base);
int animation_get_frame(Animation const *animation);
void animation_set_frame(Animation *animation, int frame);

#endif // ANIMATION_H

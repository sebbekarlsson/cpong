#ifndef PONG_ACTOR_PAD_H
#define PONG_ACTOR_PAD_H
#include <coelum/actor.h>


typedef struct ACTOR_PAD_STRUCT {
    actor_T base;
    float speed;
    int player;
    float target_x;
    float target_y;
    int target_y_error;
    int use_error;
} actor_pad_T;


actor_pad_T* init_actor_pad(float x, float y, float z, int player);

void actor_pad_tick(actor_T* self);

void actor_pad_draw(actor_T* self);
#endif

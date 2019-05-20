#ifndef PONG_ACTOR_BALL_H
#define PONG_ACTOR_BALL_H
#include <coelum/actor.h>


typedef struct ACTOR_BALL_STRUCT {
    actor_T base;
    float target_angle;
    float timer;
} actor_ball_T;


actor_ball_T* init_actor_ball(float x, float y, float z);

void actor_ball_tick(actor_T* self);

void actor_ball_draw(actor_T* self);
#endif

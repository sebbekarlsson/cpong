#include "include/actor_ball.h"
#include <coelum/constants.h>
#include <coelum/input.h>
#include <coelum/textures.h>
#include <coelum/scene_manager.h>
#include "include/scene_play.h"
#include <coelum/sound.h>
#include <coelum/utils.h>
#include <coelum/theatre.h>
#include <coelum/physics.h>
#include <string.h>


extern theatre_T* THEATRE;

void actor_ball_load(actor_T* self)
{
    physics_vec2_push(&self->dx, &self->dy, ((actor_ball_T*)self)->target_angle, 10.0f);
}

/**
 * Creates an instancec of a ball actor.
 *
 * @param float x
 * @param float y
 * @param float z
 *
 * @return actor_ball_T*
 */
actor_ball_T* init_actor_ball(float x, float y, float z)
{
    actor_ball_T* ball = calloc(1, sizeof(struct ACTOR_BALL_STRUCT));
    actor_T* a = (actor_T*) ball;

    actor_constructor(a, x, y, z, actor_ball_tick, actor_ball_draw, "ball");

    a->load = actor_ball_load;
    a->width = 16;
    a->height = 16;
    a->friction = 0.01f;
    a->sprite = init_sprite_from_file("res/img/redball.png", GL_RGBA, 1.0f, a->width, a->height);

    ball->target_angle = 0.0f;
    ball->timer = 0.0f;

    return ball;
}

void actor_ball_tick(actor_T* self)
{
    physics_tick_actor(self);

    scene_T* current_scene = scene_manager_get_current_scene(THEATRE->scene_manager);

    actor_ball_T* ball = (actor_ball_T*) self;

    // timer
    if (ball->timer > 0)
    {
        ball->timer -= 1.0f;
    }

    state_T* state = (state_T*) current_scene;

    // state->camera->x = self->x - WINDOW_WIDTH / 2;

    if (!ball->timer)
    {
        for (int i = 0; i < state->actors->size; i++)
        {
            actor_T* a = (actor_T*) state->actors->items[i];

            if (strcmp(a->type_name, "pad") == 0) // pad
            {
                if (self->x + self->width > a->x && self->x < a->x + a->width)
                {
                    if (self->y + self->height > a->y && self->y < a->y + a->height)
                    {
                        self->dx = 0.0f;
                        self->dy = 0.0f; 
                        
                        int padding = 8;

                        if (self->x + self->width < a->x + a->width / 2)
                        {
                            self->x = a->x - self->width;
                            ball->target_angle = 180.0f;
                        }
                        else
                        {
                            self->x = a->x + a->width;
                            ball->target_angle = 0.0f; 
                        }

                        if (self->y + (self->height / 2) > a->y + (a->height / 2) + padding)
                        {
                            ball->target_angle -= 10.0f;
                        }
                        else
                        if (self->y + (self->height / 2) < a->y + (a->height / 2) - padding)
                        {
                            ball->target_angle += 10.0f;
                        }
                        else
                        {
                            if (random_int(0, 3) == 0)
                            {
                                ball->target_angle -= 10.0f;
                            }
                            else
                            {
                                ball->target_angle += 10.0f;
                            }
                        }
                        
                        physics_vec2_push(&self->dx, &self->dy, ball->target_angle, 10.5f);

                        play_sound_threaded(140.0, 1.0f, THEATRE->al);
                    }
                }
            }
        }
    }

    if (self->x < 0)
    {
        scene_play_T* play_scene = (scene_play_T*) current_scene;
        play_scene->computer_score += 1;
        self->dx = 0.0f;
        self->dy = 0.0f;
        ball->target_angle -= 180.0f;

        physics_vec2_push(&self->dx, &self->dy, ball->target_angle, 10.0f);

        ball->timer = 10.0f;
        play_sound_threaded(300.0f, 1.0f, THEATRE->al);
    }

    if (self->x > WINDOW_WIDTH)
    {
        scene_play_T* play_scene = (scene_play_T*) current_scene;
        play_scene->player_score += 1;
        self->dx = 0.0f;
        self->dy = 0.0f;
        ball->target_angle -= 180.0f;
        physics_vec2_push(&self->dx, &self->dy, ball->target_angle, 10.0f);
        ball->timer = 10.0f;
        play_sound_threaded(600.0f, 1.0f, THEATRE->al);
    }

    if (self->y <= 0) // we hit the top wall
    {
        self->dx = 0.0f;
        self->dy = 0.0f;
        ball->target_angle -= 180.0f;
        physics_vec2_push(&self->dx, &self->dy, ball->target_angle, 10.0f);
    }

    if (self->y >= 480.0f) // we hit the bottom wall
    {
        self->dx = 0.0f;
        self->dy = 0.0f;
        ball->target_angle -= 180.0f;
        physics_vec2_push(&self->dx, &self->dy, ball->target_angle, 10.0f);
    }
}

void actor_ball_draw(actor_T* self)
{
    actor_draw(self);
}

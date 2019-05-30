#include "include/actor_pad.h"
#include <coelum/constants.h>
#include <coelum/input.h>
#include <coelum/textures.h>
#include <coelum/theatre.h>
#include <coelum/utils.h>
#include <time.h>
#include <string.h>


extern theatre_T* THEATRE;
extern keyboard_state_T* KEYBOARD_STATE;

extern unsigned int SHADER_COLORED;

int key_up = 0;
int key_down = 0;

void actor_pad_key_up_callback(int state)
{
    key_up = state;
}

void actor_pad_key_down_callback(int state)
{
    key_down = state;
}

/**
 * Creates an instancec of a pad actor.
 *
 * @param float x
 * @param float y
 * @param float z
 *
 * @return actor_pad_T*
 */
actor_pad_T* init_actor_pad(float x, float y, float z, int player)
{
    actor_pad_T* pad = calloc(1, sizeof(struct ACTOR_PAD_STRUCT));
    actor_T* a = (actor_T*) pad;

    actor_constructor(a, x, y, z, actor_pad_tick, actor_pad_draw, "pad");
    
    a->shader_program = SHADER_COLORED;
    a->width = 16;
    a->height = 48;

    pad->player = player;
    pad->speed = 4.5f;
    pad->target_x = WINDOW_WIDTH / 2;
    pad->target_y = y;
    pad->target_y_error = 0.0f;
    pad->use_error = 0;

    return pad;
}

void actor_pad_tick(actor_T* self)
{
    actor_pad_key_up_callback(KEYBOARD_STATE->keys[GLFW_KEY_UP]);
    actor_pad_key_down_callback(KEYBOARD_STATE->keys[GLFW_KEY_DOWN]);

    actor_pad_T* pad = (actor_pad_T*) self;

    if (pad->player)
    {
        if (key_up && self->y > 0)
            self->y -= ((actor_pad_T*)self)->speed;

        if (key_down && self->y + self->height < WINDOW_HEIGHT)
            self->y += ((actor_pad_T*)self)->speed;
    }
    else
    {
        scene_T* current_scene = scene_manager_get_current_scene(THEATRE->scene_manager);
        state_T* state = (state_T*) current_scene;

        actor_T* player = (void*) 0;
        actor_T* ball = (void*) 0;

        for (int i = 0; i < state->actors->size; i++)
        {
            actor_T* a = (actor_T*) state->actors->items[i];

            if (strcmp(a->type_name, "ball") == 0) // ball
            {
                ball = a;
            }
            else
            if (strcmp(a->type_name, "pad") == 0 && a != self)
            {
                player = a;
            }
        }

        pad->target_y = ball->y;
        
        int chance = 32;

        if (ball->x < WINDOW_WIDTH / 2)
            chance -= 8;

        if (pad->use_error)
        {
            pad->target_y += pad->target_y_error;
            chance = 8;
        }

        if (random_int(0, chance) == 1) // toggle error on and off
        {
            if (pad->use_error)
                pad->use_error = 0;
            else
                pad->use_error = 1;
        }

        if (random_int(0, 8) == 0)
        {
            pad->target_y_error = random_int(-WINDOW_HEIGHT, WINDOW_HEIGHT);
        }

        if (self->y < pad->target_y)
        {
            self->y += pad->speed;
        }
        else
        if (self->y > pad->target_y)
        {
            self->y -= pad->speed;
        }
    }
}

void actor_pad_draw(actor_T* self)
{
    actor_draw(self);
}

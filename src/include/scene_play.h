#ifndef PONG_SCENE_PLAY_H
#define PONG_SCENE_PLAY_H
#include <coelum/scene.h>
#include <coelum/actor_text.h>


typedef struct SCENE_PLAY_STRUCT {
    scene_T base;
    int player_score;
    int computer_score;
    actor_text_T* text_player_score;
    actor_text_T* text_computer_score;
    char* text_player_score_buffer;
    char* text_computer_score_buffer;
} scene_play_T;

scene_play_T* init_scene_play();

void scene_play_tick(state_T* state);

void scene_play_draw(state_T* state);
#endif

#ifndef PONG_SCENE_MENU_H
#define PONG_SCENE_MENU_H
#include <coelum/scene.h>
#include <coelum/dynamic_list.h>


typedef struct SCENE_MENU_STRUCT {
    scene_T base;
    int button_index;
    dynamic_list_T* buttons;
    dynamic_list_T* event_listeners;
} scene_menu_T;

scene_menu_T* init_scene_menu();

void scene_menu_tick(state_T* self);

void scene_menu_draw(state_T* self);
#endif

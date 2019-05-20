#include "include/scene_menu.h"
#include "include/actor_pad.h"
#include <coelum/constants.h>
#include <coelum/actor_text.h>
#include <coelum/input.h>
#include <coelum/scene_manager.h>


extern scene_manager_T* SCENE_MANAGER;
extern keyboard_state_T* KEYBOARD_STATE;
extern GLFWwindow* window;

void scene_menu_key_enter_callback(scene_menu_T* s_menu, int state)
{

    if (state)
    {
        switch (s_menu->button_index)
        {
            case 0:
                // "play" button
                
                scene_manager_next(SCENE_MANAGER);
            break;
            case 1:
                // "quit" button
                
                glfwSetWindowShouldClose(window, 1);
            break;
        }
    }
}

void scene_menu_key_up_callback(scene_menu_T* s_menu, int state)
{
    if (state)
    {
        if (s_menu->button_index > 0)
            s_menu->button_index -= 1;
    }
}

void scene_menu_key_down_callback(scene_menu_T* s_menu, int state)
{
    if (state)
    {
        if (s_menu->button_index < s_menu->buttons->size - 1)
            s_menu->button_index += 1;
    }
}

/**
 * Creates a new scene_menu
 *
 * @return scene_menu_T*
 */
scene_menu_T* init_scene_menu()
{
    scene_menu_T* s_menu = calloc(1, sizeof(struct SCENE_MENU_STRUCT));
    scene_T* s = (scene_T*) s_menu;

    scene_constructor(s, scene_menu_tick, scene_menu_draw);

    s_menu->button_index = 0;
    s_menu->buttons = init_dynamic_list(sizeof(struct ACTOR_TEXT_STRUCT));

    actor_text_T* play_button = init_actor_text((WINDOW_WIDTH / 2) - ((3 * 24) / 2), (WINDOW_HEIGHT / 2) - 16, 0.0f, "play", 255, 255, 255);
    actor_text_T* quit_button = init_actor_text((WINDOW_WIDTH / 2) - ((3 * 24) / 2), (WINDOW_HEIGHT / 2) + 16, 0.0f, "quit", 255, 255, 255);
    dynamic_list_append(s->actors, play_button);
    dynamic_list_append(s_menu->buttons, play_button);
    dynamic_list_append(s->actors, quit_button);
    dynamic_list_append(s_menu->buttons, quit_button);

    return s_menu;
}

void scene_menu_tick(scene_T* self)
{
    scene_tick(self);

    scene_menu_T* s_menu = (scene_menu_T*) self;

    scene_menu_key_up_callback(s_menu, KEYBOARD_STATE->keys[GLFW_KEY_UP]);
    scene_menu_key_down_callback(s_menu, KEYBOARD_STATE->keys[GLFW_KEY_DOWN]);
    scene_menu_key_enter_callback(s_menu, KEYBOARD_STATE->keys[GLFW_KEY_ENTER]);

    for (int i = 0; i < s_menu->buttons->size; i++)
    {
        actor_text_T* a_t = (actor_text_T*) s_menu->buttons->items[i];

        if (s_menu->button_index == i)
        {
            a_t->r = 255.0f;
            a_t->g = 0.0f;
            a_t->b = 0.0f;
        }
        else
        {
            a_t->r = 255.0f;
            a_t->g = 255.0f;
            a_t->b = 255.0f;
        }
    }
}

void scene_menu_draw(scene_T* self)
{
    scene_draw(self);
}

#include <coelum/main.h>
#include <coelum/scene_manager.h>
#include "include/scene_menu.h"
#include "include/scene_play.h"


extern scene_manager_T* SCENE_MANAGER;

int main(int argc, char* argv[])
{
    coelum_init();

    scene_manager_register_scene(SCENE_MANAGER, (scene_T*) init_scene_menu());
    scene_manager_register_scene(SCENE_MANAGER, (scene_T*) init_scene_play());

    return coelum_main(argc, argv, 1);
}

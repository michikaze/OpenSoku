#include "../global_types.h"
#include "../scene.h"
#include "menus.h"

screen_gameplay::screen_gameplay()
{
    scene = scene_get_scene();
}

id_screen screen_gameplay::update()
{
    int32_t t = scene->update();
    switch (t)
    {
        case 1:
        /*if ( gameplay_type_get() == GAMEPLAY_REPLAY ) //HACK
    return 2;
  if ( !game_type_get() || (v3 = game_type_get() == GAME_TYPE_ARCADE, result = 3, v3) )
    result = 16;
  return result;*/
        return SCREEN_MAIN; // HACK
        case 2:
        return SCREEN_MAIN;
        case 3:
        return (id_screen)20;

        case 0:
        default:
        return SCREEN_GAMEPLAY;
    }
    return SCREEN_MAIN;
}

bool screen_gameplay::draw()
{
    gr_clear(126,206,244);
    if (true)//HACK DON'T NEED FRAME SKIP?
    {
        scene->func14();
        return true;
    }

    return false;
}


id_screen screen_gameplay::getID()
{
    return SCREEN_GAMEPLAY;
}
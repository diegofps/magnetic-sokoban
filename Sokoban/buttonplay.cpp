#include "buttonplay.h"
#include "mouselistener.h"
#include "graphics.h"
#include "engine.h"
#include "sprite.h"

ButtonPlay::ButtonPlay(Engine *engine, Room *nextRoom) :
    Object(engine), Button(engine,
        new Sprite(engine->graphics()->newImage(":imgs/button_play_normal.svg"),1,1,1,0),
        new Sprite(engine->graphics()->newImage(":imgs/button_play_hover.svg" ),1,1,1,0),
        new Sprite(engine->graphics()->newImage(":imgs/button_play_press.svg" ),1,1,1,0)),
    _nextRoom(nextRoom)
{
    x( (engine->graphics()->viewport().width() - sprite()->width()) / 2 );
    y( engine->graphics()->viewport().height() - sprite()->height() * 4 );
}

void ButtonPlay::onClick(int buttons)
{
    if (buttons | MouseListener::BUTTON_LEFT)
        engine()->goTo(_nextRoom);
}

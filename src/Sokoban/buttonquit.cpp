#include "buttonquit.h"
#include "mouselistener.h"
#include "engine.h"
#include "sprite.h"
#include "engine.h"
#include "graphics.h"

ButtonQuit::ButtonQuit(Engine *engine) : Object(engine), Button(engine,
        new Sprite(engine->graphics()->newImage(":imgs/button_quit_normal.svg"),1,1,1,0),
        new Sprite(engine->graphics()->newImage(":imgs/button_quit_hover.svg" ),1,1,1,0),
        new Sprite(engine->graphics()->newImage(":imgs/button_quit_press.svg" ),1,1,1,0))
{
    x( (engine->graphics()->viewport().width() - sprite()->width()) / 2 );
    y( engine->graphics()->viewport().height() - sprite()->height() * 2 );
}

void ButtonQuit::onClick(int buttons)
{
    if (buttons | MouseListener::BUTTON_LEFT)
        engine()->endGame();
}

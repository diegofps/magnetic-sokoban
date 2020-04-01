#include "button.h"
#include "engine.h"
#include "buttonlistener.h"
#include "helpers.h"
#include "room.h"

Button::Button(Engine *engine, Room *room, Sprite *normal, Sprite *hover, Sprite *press, ButtonListener *listener) :
    Object(engine), MouseListener(engine),
    _normal(normal), _hover(hover), _press(press), _listener(listener)
{
    sprite(_normal);
    room->addMouseListener(this);
}

void Button::onButtonRelease(const MouseListener::Buttons, const int, const int)
{
    sprite(_normal);
    if (_listener != NULL)
        _listener->onClick(this);
}

void Button::onMouseMove(const MouseListener::Buttons buttons, const int x, const int y, const int, const int)
{
    if (helpers::pointInsideBox(x, y, this->x(), this->y(), this->width(), this->height()))
        if (buttons) sprite(_press);
        else sprite(_hover);
    else sprite(_normal);
}

void Button::onButtonPress(const MouseListener::Buttons, const int, const int)
{
    sprite(_press);
}

void Button::onMouseEnter(const MouseListener::Buttons, const int, const int)
{
    sprite(_hover);
}

void Button::onMouseLeave(const MouseListener::Buttons, const int, const int)
{
    sprite(_normal);
}

void Button::spriteNormal(Sprite *normal)
{
    if (sprite() == _normal) sprite(normal);
    _normal = normal;
}

void Button::spriteHover(Sprite *hover)
{
    if (sprite() == _hover) sprite(hover);
    _hover = hover;
}

void Button::spritePress(Sprite *press)
{
    if (sprite() == _press) sprite(press);
    _press = press;
}

void Button::listener(ButtonListener *listener)
{
    _listener = listener;
}

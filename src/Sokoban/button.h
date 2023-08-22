#ifndef BUTTON_H
#define BUTTON_H

#include "object.h"
#include "mouselistener.h"

class Sprite;
class Engine;
class ButtonListener;
class Room;

class Button : virtual public Object, public MouseListener
{

public:

    Button(Engine *engine, Room *room, Sprite *normal, Sprite *hover, Sprite *press, ButtonListener *listener);

    virtual ~Button() { }

    void spriteNormal(Sprite *normal);

    void spriteHover(Sprite *hover);

    void spritePress(Sprite *press);

    void listener(ButtonListener *listener);

    virtual void onButtonPress(const Buttons buttons, const int x, const int y);

    virtual void onMouseMove(const Buttons buttons, const int x, const int y, const int lastX, const int lastY);

    virtual void onButtonRelease(const Buttons buttons, const int x, const int y);

    virtual void onMouseEnter(const Buttons buttons, const int x, const int y);

    virtual void onMouseLeave(const Buttons buttons, const int x, const int y);

private:

    Sprite *_normal;

    Sprite *_hover;

    Sprite *_press;

    ButtonListener *_listener;

};

#endif // BUTTON_H

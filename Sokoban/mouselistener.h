#ifndef MOUSELISTENER_H
#define MOUSELISTENER_H

#include "object.h"

class MouseListener : virtual public Object
{

public:

    enum Buttons { NONE = 0, BUTTON_LEFT = 1, BUTTON_RIGHT = 2, BUTTON_MIDDLE = 4 };

    MouseListener(Engine *engine) : Object(engine) { }

    virtual ~MouseListener() { }

    virtual void onButtonPress(const Buttons buttons, const int x, const int y) = 0;

    virtual void onMouseMove(const Buttons buttons, const int x, const int y, const int lastX, const int lastY) = 0;

    virtual void onButtonRelease(const Buttons buttons, const int x, const int y) = 0;

    virtual void onMouseEnter(const Buttons buttons, const int x, const int y) = 0;

    virtual void onMouseLeave(const Buttons buttons, const int x, const int y) = 0;

};

inline MouseListener::Buttons operator|(const MouseListener::Buttons a, const MouseListener::Buttons b)
{
    return MouseListener::Buttons(int(a)|int(b));
}

inline MouseListener::Buttons operator |=(MouseListener::Buttons a, const MouseListener::Buttons b)
{
    return a = a | b;
}

#endif // MOUSELISTENER_H

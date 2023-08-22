#ifndef QGAMEWIDGETLISTENER_H
#define QGAMEWIDGETLISTENER_H

#include "mouselistener.h"
#include "keylistener.h"

class QGameWidgetListener
{

public:

    ~QGameWidgetListener() { }

    virtual void onStep() = 0;

    virtual void onPaint() = 0;

    virtual void onMousePress(const MouseListener::Buttons buttons, const int x, const int y) = 0;

    virtual void onMouseMove(const MouseListener::Buttons buttons, const int x, const int y) = 0;

    virtual void onMouseRelease(const MouseListener::Buttons buttons, const int x, const int y) = 0;

    virtual void onKeyPress(KeyListener::Key key) = 0;

    virtual void onKeyRelease(KeyListener::Key key) = 0;

};

#endif // QGAMEWIDGETLISTENER_H

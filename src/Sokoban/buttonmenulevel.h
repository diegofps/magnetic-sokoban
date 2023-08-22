#ifndef BUTTONMENULEVEL_H
#define BUTTONMENULEVEL_H

#include "button.h"
#include "mouselistener.h"

class LevelSelectRoom;
class Sprite;
class Graphics;

class ButtonMenuLevel : public Button
{

public:

    static const int ARROW_LEFT = -1;

    static const int ARROW_RIGHT = -2;

    static const int NOTHING = -3;

public:

    ButtonMenuLevel(Engine *engine, Room *room, Sprite *normal, Sprite *hover, Sprite *press, ButtonListener *listener, Sprite *numbers, int level);

    virtual void draw(const Viewport & viewport, Graphics * g);

    virtual void modalDraw(const Viewport & viewport, Graphics * g);

    void level(int level);

    void star(Sprite *star);

private:

    Sprite *_numbers;

    char _title[10];

    Sprite *_star;

};

#endif // BUTTONMENULEVEL_H

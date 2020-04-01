#ifndef MENUROOM_H
#define MENUROOM_H

#include "room.h"
#include "buttonlistener.h"

class Object;
class Engine;
class LevelSelectRoom;
class Sprite;

class MenuRoom : public Room, public ButtonListener, public KeyListener
{

public:

    MenuRoom(Engine *engine);

    ~MenuRoom();

    void onEnter();

    void onLeave();

    void onClick(Button *button);

    void onKeyPress(Key key);

private:

    LevelSelectRoom *_levelSelectRoom;

    Sprite *_spriteButtonPlayNormal;

    Sprite *_spriteButtonPlayHover;

    Sprite *_spriteButtonPlayPress;

    Sprite *_spriteButtonQuitNormal;

    Sprite *_spriteButtonQuitHover;

    Sprite *_spriteButtonQuitPress;

    Object *_buttonPlay;

    Object *_buttonQuit;

    Object *_title;

};

#endif // MENUROOM_H

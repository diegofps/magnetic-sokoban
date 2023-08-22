#ifndef MODALROOMFINISHLEVEL_H
#define MODALROOMFINISHLEVEL_H

#include "room.h"
#include "buttonlistener.h"
#include "keylistener.h"

class SpritesHandler;

class ModalRoomFinishLevel : public Room, public ButtonListener, public KeyListener
{

public:

    static const int RESULT_MENU = 0;

    static const int RESULT_RESTART = 1;

    static const int RESULT_NEXT = 2;

public:

    ModalRoomFinishLevel(Engine *engine, Room *parent, SpritesHandler *spritesHandler);

    void steps(const int robotSteps, const int stepsForGold, const int stepsForSilver, const int stepsForBronze);

    virtual void onEnter();

    virtual void onClick(Button *button);

    virtual void onKeyRelease(KeyListener::Key key);

private:

    SpritesHandler *_spritesHandler;

    Sprite *_star;

    Button *_btMenu;

    Button *_btRestart;

    Button *_btNext;

    int _robotSteps;

    int _stepsForGold;

    int _stepsForSilver;

    int _stepsForBronze;

};

#endif // MODALROOMFINISHLEVEL_H

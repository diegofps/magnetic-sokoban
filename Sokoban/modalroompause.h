#ifndef MODALROOMPAUSE_H
#define MODALROOMPAUSE_H

#include "room.h"
#include "keylistener.h"
#include "buttonlistener.h"

class GameRoom;
class SpritesHandler;

class ModalRoomPause : public Room, public KeyListener, public ButtonListener
{

public:

    static const int RESULT_MENU    = 0;
    static const int RESULT_RESTART = 1;
    static const int RESULT_RESUME  = 2;

public:

    ModalRoomPause(Engine *engine, GameRoom *parent, SpritesHandler * spritesHandler);

    virtual void onEnter();

    virtual void onKeyRelease(Key key);

    virtual void onClick(Button *button);

    void steps(const int robotSteps, const int stepsForGold, const int stepsForSilver, const int stepsForBronze);

private:

    SpritesHandler *_spritesHandler;

    Button * _btMenu;

    Button * _btRestart;

    Button * _btResume;

    int _robotSteps;

    int _stepsForGold;

    int _stepsForSilver;

    int _stepsForBronze;

};

#endif // MODALROOMPAUSE_H

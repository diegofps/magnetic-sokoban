#ifndef ROBOT_H
#define ROBOT_H

#include "levelobject.h"
#include "keylistener.h"
#include "steplistener.h"
#include "viewportrefresher.h"

class GameRoom;
class SpritesHandler;

class Robot : public LevelObject, public KeyListener, public ViewportRefresher
{

public:

    static const int SPEED = 5;

    Robot(Engine *engine, GameRoom *gameRoom, const int x, const int y, const MapObject::Direction direction, SpritesHandler *spritesHandler);

    virtual void onKeyPress(Key key);

    virtual void onKeyRelease(Key key);

    virtual void refresh(Viewport & viewport);

    virtual void onIdle();

    virtual void onFinishMove();

private:

    GameRoom * _gameRoom;

    SpritesHandler *_spritesHandler;

    bool _up;

    bool _down;

    bool _left;

    bool _right;

};

#endif // ROBOT_H

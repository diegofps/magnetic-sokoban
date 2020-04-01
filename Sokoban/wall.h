#ifndef WALL_H
#define WALL_H

#include "levelobject.h"

class GameRoom;
class SpritesHandler;

class Wall : public LevelObject
{

public:

    Wall(Engine *engine, GameRoom *gameRoom, const int x, const int y, bool isRigid, SpritesHandler *spritesHandler,
         MapObject::Material north, MapObject::Material south,
         MapObject::Material east, MapObject::Material west);

    virtual void draw(const Viewport &viewport, Graphics *g);

    virtual void modalDraw(const Viewport &viewport, Graphics *g);

    virtual void onIdle();

    virtual void onFinishMove();

private:

    GameRoom *_gameRoom;

    SpritesHandler *_spritesHandler;

    Sprite * _back;

    Sprite * _plateNorth;

    Sprite * _plateSouth;

    Sprite * _plateEast;

    Sprite * _plateWest;

};

#endif // WALL_H

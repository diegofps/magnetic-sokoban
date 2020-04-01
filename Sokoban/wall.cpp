#include "wall.h"
#include "graphics.h"
#include "viewport.h"
#include "spriteshandler.h"
#include "sprite.h"
#include "gameroom.h"

Wall::Wall(Engine *engine, GameRoom *gameRoom, const int x, const int y,
           bool isRigid, SpritesHandler *spritesHandler,
           MapObject::Material north, MapObject::Material south,
           MapObject::Material east, MapObject::Material west) :
    LevelObject(engine, x, y),
    _gameRoom(gameRoom), _spritesHandler(spritesHandler)
{
    if (isRigid) _back = spritesHandler->rigidWall();
    else _back = spritesHandler->movableWall();

    rigid(isRigid);
    northMaterial(north);
    southMaterial(south);
    eastMaterial(east);
    westMaterial(west);

    switch(north) {
    case MapObject::MagneticNorth: _plateNorth = spritesHandler->plateMagneticNorthNorth(); break;
    case MapObject::MagneticSouth: _plateNorth = spritesHandler->plateMagneticSouthNorth(); break;
    case MapObject::Metal: _plateNorth = spritesHandler->plateMetalNorth(); break;
    default: _plateNorth = NULL; break;
    }

    switch(south) {
    case MapObject::MagneticNorth: _plateSouth = spritesHandler->plateMagneticNorthSouth(); break;
    case MapObject::MagneticSouth: _plateSouth = spritesHandler->plateMagneticSouthSouth(); break;
    case MapObject::Metal: _plateSouth = spritesHandler->plateMetalSouth(); break;
    default: _plateSouth = NULL; break;
    }

    switch(east) {
    case MapObject::MagneticNorth: _plateEast = spritesHandler->plateMagneticNorthEast(); break;
    case MapObject::MagneticSouth: _plateEast = spritesHandler->plateMagneticSouthEast(); break;
    case MapObject::Metal: _plateEast = spritesHandler->plateMetalEast(); break;
    default: _plateEast = NULL; break;
    }

    switch(west) {
    case MapObject::MagneticNorth: _plateWest = spritesHandler->plateMagneticNorthWest(); break;
    case MapObject::MagneticSouth: _plateWest = spritesHandler->plateMagneticSouthWest(); break;
    case MapObject::Metal: _plateWest = spritesHandler->plateMetalWest(); break;
    default: _plateWest = NULL; break;
    }
}

void Wall::draw(const Viewport &viewport, Graphics *g)
{
    int drawX = x() - viewport.x();
    int drawY = y() - viewport.y();

    _back->draw(g, drawX, drawY);

    if (_plateNorth != NULL)
        _plateNorth->draw(g, drawX, drawY);

    if (_plateSouth != NULL)
        _plateSouth->draw(g, drawX, drawY);

    if (_plateEast != NULL)
        _plateEast->draw(g, drawX, drawY);

    if (_plateWest != NULL)
        _plateWest->draw(g, drawX, drawY);
}

void Wall::modalDraw(const Viewport &viewport, Graphics *g)
{
    draw(viewport, g);
}

void Wall::onIdle()
{
    if (_gameRoom->isObjective(toX(), toY()))
        _back = _spritesHandler->atObjectiveWall();

    else if (connected())
        _back = _spritesHandler->bindedWall();

    else if (rigid())
        _back = _spritesHandler->rigidWall();

    else
        _back = _spritesHandler->movableWall();
}

void Wall::onFinishMove()
{

}

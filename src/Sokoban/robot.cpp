#include "robot.h"
#include "spriteshandler.h"
#include "engine.h"
#include <viewport.h>
#include "gameroom.h"

Robot::Robot(Engine *engine, GameRoom *gameRoom, const int x, const int y, const MapObject::Direction direction, SpritesHandler *spritesHandler) :
    LevelObject(engine, x, y),
    _gameRoom(gameRoom), _spritesHandler(spritesHandler),
    _up(false), _down(false), _left(false), _right(false)
{
    switch(direction) {
    case MapObject::North: sprite(spritesHandler->robotNorth()); break;
    case MapObject::South: sprite(spritesHandler->robotSouth()); break;
    case MapObject::East: sprite(spritesHandler->robotEast()); break;
    default: sprite(spritesHandler->robotWest()); break;
    }

    rigid(false);
    canConnectToObjective(false);
    northMaterial(MapObject::Neutral);
    southMaterial(MapObject::Neutral);
    eastMaterial(MapObject::Neutral);
    westMaterial(MapObject::Neutral);

    gameRoom->addKeyListener(this);
    gameRoom->setViewportRefresher(this);
}

void Robot::onKeyPress(KeyListener::Key key)
{
    if (key == KeyListener::Left) _left = true;
    if (key == KeyListener::Right) _right = true;
    if (key == KeyListener::Up) _up = true;
    if (key == KeyListener::Down) _down = true;
}

void Robot::onKeyRelease(KeyListener::Key key)
{
    if (key == KeyListener::Left) _left = false;
    if (key == KeyListener::Right) _right = false;
    if (key == KeyListener::Up) _up = false;
    if (key == KeyListener::Down) _down = false;
}

void Robot::onIdle()
{
    if (sprite() == _spritesHandler->robotMoveNorth()
            || sprite() == _spritesHandler->robotMoveSouth()
            || sprite() == _spritesHandler->robotNorth()
            || sprite() == _spritesHandler->robotSouth() )
    {

        if (_left) {
            sprite(_spritesHandler->robotMoveWest());
            move(MapObject::West);
        }

        else if (_right) {
            sprite(_spritesHandler->robotMoveEast());
            move(MapObject::East);
        }

        else if (_up) {
            sprite(_spritesHandler->robotMoveNorth());
            move(MapObject::North);
        }

        else if (_down) {
            sprite(_spritesHandler->robotMoveSouth());
            move(MapObject::South);
        }

        else if (sprite() == _spritesHandler->robotMoveNorth()){
            sprite(_spritesHandler->robotNorth());
        }

        else if (sprite() == _spritesHandler->robotMoveSouth()){
            sprite(_spritesHandler->robotSouth());
        }

        else if (sprite() == _spritesHandler->robotMoveEast()){
            sprite(_spritesHandler->robotEast());
        }

        else if (sprite() == _spritesHandler->robotMoveWest()){
            sprite(_spritesHandler->robotWest());
        }

    }

    else if (sprite() == _spritesHandler->robotMoveEast()
             || sprite() == _spritesHandler->robotMoveWest()
             || sprite() == _spritesHandler->robotEast()
             || sprite() == _spritesHandler->robotWest() )
    {

        if (_up) {
            sprite(_spritesHandler->robotMoveNorth());
            move(MapObject::North);
        }

        else if (_down) {
            sprite(_spritesHandler->robotMoveSouth());
            move(MapObject::South);
        }

        else if (_left) {
            sprite(_spritesHandler->robotMoveWest());
            move(MapObject::West);
        }

        else if (_right) {
            sprite(_spritesHandler->robotMoveEast());
            move(MapObject::East);
        }

        else if (sprite() == _spritesHandler->robotMoveNorth()){
            sprite(_spritesHandler->robotNorth());
        }

        else if (sprite() == _spritesHandler->robotMoveSouth()){
            sprite(_spritesHandler->robotSouth());
        }

        else if (sprite() == _spritesHandler->robotMoveEast()){
            sprite(_spritesHandler->robotEast());
        }

        else if (sprite() == _spritesHandler->robotMoveWest()){
            sprite(_spritesHandler->robotWest());
        }

    }

}

void Robot::refresh(Viewport &viewport)
{
    int levelWidth = _gameRoom->width() * 48;
    int levelHeight = _gameRoom->height() * 48;

    if (viewport.width() >= levelWidth) {
        viewport.x( - (viewport.width() - levelWidth) / 2 );
    }

    else {
        viewport.x( x() - (viewport.width() - width()) / 2 );

        if (viewport.x() < 0)
            viewport.x( 0 );
        else if (viewport.x() + viewport.width() > levelWidth)
            viewport.x( levelWidth - viewport.width() );
    }

    if (viewport.height() >= levelHeight) {
        viewport.y( - (viewport.height() - levelHeight) / 2 );
    }

    else {
        viewport.y( y() - (viewport.height() - height()) / 2 );

        if (viewport.y() < 0)
            viewport.y( 0 );
        else if (viewport.y() + viewport.height() > levelHeight)
            viewport.y( levelHeight - viewport.height() );
    }
}

void Robot::onFinishMove()
{
}

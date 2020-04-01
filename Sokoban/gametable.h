#ifndef GAMETABLE_H
#define GAMETABLE_H

#include <map>

#include "object.h"
#include "keylistener.h"
#include "steplistener.h"
#include "mapobject.h"

class GameRoom;
class LevelObject;
class SpritesHandler;
class Map;

class GameTable : public Object, public StepListener, public KeyListener
{

private:
/*
    class Position {

    public:

        Position(int _mapWidth, int _x, int _y) :
            mapWidth(_mapWidth), x(_x), y(_y) { }

        bool operator < (const Position & other) {
            return y * mapWidth + x < other.y * other.mapWidth + other.x;
        }

        int x;
        int y;

    private:

        int mapWidth;

    };
*/
    class LevelObject {

    public:

        static const int ANIM_FRAMES = 10;

    public:

        LevelObject() :
            _north(MapObject::Neutral), _south(MapObject::Neutral),
            _east(MapObject::Neutral), _west(MapObject::Neutral),
            _isMoving(false), _isOrig(false), _isObjective(false),
            _isEmpty(true), _isMovable(false), _isBind(false),
            _isRobot(false), _movingFrame(0), _sprite(NULL),
            _aboutToMove(false) { }

        bool isMoving() { return _isMoving; }

        bool isOrig() { return _isOrig; }

        bool isObjective() { return _isObjective; }

        bool isEmpty() { return _isEmpty; }

        bool isMovable() { return _isMovable; }

        bool isBind() { return _isBind; }

        bool isRobot() { return _isRobot; }

        MapObject::Direction movingDirection() { return _movingDirection; }

        MapObject::Direction gazeDirection() { return _gazeDirection; }

        MapObject::Material north() { return _north; }

        MapObject::Material south() { return _south; }

        MapObject::Material east() { return _east; }

        MapObject::Material west() { return _west; }

        Sprite * sprite() { return _sprite; }


        void isMoving(bool isMoving) { _isMoving = isMoving; _movingFrame = 0; _aboutToMove = false; }

        void isOrig(bool isOrig) { _isOrig = isOrig; }

        void isObjective(bool isObjective) { _isObjective = isObjective; }

        void isEmpty(bool isEmpty) { _isEmpty = isEmpty; }

        void isMovable(bool isMovable) { _isMovable = isMovable; }

        void isBind(bool isBind) { _isBind = isBind; }

        void isRobot(bool isRobot) { _isRobot = isRobot; }

        void movingDirection(MapObject::Direction direction) { aboutToMove(); _movingDirection = direction; }

        void gazeDirection(MapObject::Direction direction) { _gazeDirection = direction; }

        void north(MapObject::Material material) { _north = material; }

        void south(MapObject::Material material) { _south = material; }

        void east(MapObject::Material material) { _east = material; }

        void west(MapObject::Material material) { _west = material; }

        void sprite(Sprite *sprite) { _sprite = sprite; }


        void incMovingFrame() { ++_movingFrame; }

        bool atLastMovingFrame() { return _movingFrame >= ANIM_FRAMES; }

        float movingFrameInterpolation() { return (float)_movingFrame / ANIM_FRAMES; }

        bool isAboutToMove() { return _aboutToMove; }

        void aboutToMove() { _aboutToMove = true; }

    private:

        MapObject::Material _north;

        MapObject::Material _south;

        MapObject::Material _east;

        MapObject::Material _west;

        MapObject::Direction _movingDirection;

        MapObject::Direction _gazeDirection;

        bool _isMoving;

        bool _isOrig;

        bool _isObjective;

        bool _isEmpty;

        bool _isMovable;

        bool _isBind;

        bool _isRobot;

        int _movingFrame;

        Sprite *_sprite;

        bool _aboutToMove;

    };

public:

    GameTable(Engine * engine, GameRoom *gameRoom, Map * map, SpritesHandler *spritesHandler);

    virtual void onStep();

    virtual void draw(const Viewport &viewport, Graphics *g);

    virtual void onKeyPress(Key key);

    virtual void onKeyRelease(Key key);

private:

    void createTable(Map *map);

    void createLevelObject(LevelObject &levelObject, const MapObject &mapObject, const int x, const int y);

    void drawRobot(const Viewport &v, Graphics *g, LevelObject *currentObject, const int drawX, const int drawY);

    void drawWall(const Viewport &v, Graphics *g, LevelObject *currentObject, int drawX, int drawY);

    bool hasAttraction(MapObject::Material m1, MapObject::Material m2);

    bool hasRepulsion(MapObject::Material m1, MapObject::Material m2);

    void finishMoving(LevelObject *currentObject, int index2, std::map<int, LevelObject*>::iterator &it);

private:

    GameRoom *_gameRoom;

    LevelObject *_table;

    SpritesHandler *_spritesHandler;

    int _robotIndex;

    bool _up;

    bool _down;

    bool _left;

    bool _right;

    int _width;

    int _height;

    std::map<int, LevelObject*> _levelObjects;

};

#endif // GAMETABLE_H

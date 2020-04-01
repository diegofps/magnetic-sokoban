#ifndef GAMEROOM_H
#define GAMEROOM_H

#include "room.h"
#include "spriteshandler.h"
#include "mapobject.h"
#include "steplistener.h"
#include <map>

class Engine;
class Background;
class MapPack;
class LevelObject;
class Floor;
class MapObject;
class LevelObject;
class Robot;
class ModalRoomFinishLevel;
class ModalRoomPause;
class GameProgress;

class GameRoom : public Room, public KeyListener, public StepListener
{

public:

    GameRoom(Engine *engine, MapPack *mapPack, Room * previousRoom, GameProgress *gameProgress);

    void setLevel(int level);

    void onEnter();

    int width();

    int height();

    bool isObjective(const int x, const int y);

    virtual void onKeyRelease(Key key);

    virtual void onModalRoomClose(Room *modalRoom, int resultCode);

    virtual void onStep();

private:

    void createLevel();

    void addObjectFrom(const MapObject &mapObject, const int x, const int y);

    LevelObject * levelObjectAt(const int x, const int y);

    bool hasAttraction(MapObject::Material m1, MapObject::Material m2);

    bool hasRepulsion(MapObject::Material m1, MapObject::Material m2);

private:

    int _level;

    Background *_gameBackground;

    MapPack *_mapPack;

    LevelObject **_objects;

    std::map<int, bool> _objectives;

    int _width;

    int _height;

    SpritesHandler *_spritesHandler;

    ModalRoomPause * _pauseRoom;

    ModalRoomFinishLevel * _finishLevelRoom;

    Room * _previousRoom;

    Robot *_robot;

    std::vector<LevelObject*> _levelObjects;

    GameProgress *_gameProgress;

};

#endif // GAMEROOM_H

#include "gameroom.h"
#include "engine.h"
#include "graphics.h"
#include "motionbackground.h"
#include "mappack.h"
#include "floor.h"
#include "wall.h"
#include "robot.h"
#include "spriteshandler.h"
#include "modalroompause.h"
#include <iostream>
#include "modalroomfinishlevel.h"
#include "gameprogress.h"
#include <QTime>

GameRoom::GameRoom(Engine *engine, MapPack *mapPack, Room * previousRoom, GameProgress *gameProgress) :
    Room(engine),
    _level(0), _mapPack(mapPack), _objects(NULL),
    _spritesHandler(new SpritesHandler(engine->graphics())), _previousRoom(previousRoom),
    _robot(NULL), _gameProgress(gameProgress)
{
    Image * background = engine->graphics()->newImage(":imgs/game_wallpaper.svg");
    _gameBackground = engine->graphics()->newMotionBackground(background, 0, 0);
    addBackground(_gameBackground);

    _pauseRoom = new ModalRoomPause(engine, this, _spritesHandler);
    _finishLevelRoom = new ModalRoomFinishLevel(engine, this, _spritesHandler);
}

void GameRoom::setLevel(int level)
{
    _level = level;
}

void GameRoom::onEnter()
{
    createLevel();
    addStepListener(this);
    addKeyListener(this);
}

void GameRoom::createLevel()
{
    _robot = NULL;

    _objectives.clear();
    _levelObjects.clear();

    if (_objects != NULL)
        delete _objects;

    Map *map = _mapPack->at(_level);

    _width = map->width();
    _height = map->height();

    _objects = new LevelObject*[_width * _height];

    int x, y;
    for (x=0;x<map->width();++x)
        for(y=0;y<map->height();++y)
            addObjectFrom(map->at(x, y), x, y);

}

void GameRoom::addObjectFrom(const MapObject &mapObject, const int x, const int y)
{
    if (mapObject.type() == MapObject::Floor) {
        Floor *floor = new Floor(engine(), mapObject.isObjective(), _spritesHandler);
        floor->x( x * 48 );
        floor->y( y * 48 );
        if (mapObject.isObjective()) _objectives.insert(std::pair<int, bool>(y * _width + x, true));
        addObject(0, floor);
    }

    else if (mapObject.type() == MapObject::Robot) {
        Floor *floor = new Floor(engine(), false, _spritesHandler);
        floor->x( x * 48 );
        floor->y( y * 48 );
        addObject(0, floor);

        _robot = new Robot(engine(), this, x, y, mapObject.direction(), _spritesHandler);
        _levelObjects.push_back(_robot);
        addObject(2, _robot);
    }

    else if (mapObject.type() == MapObject::Wall) {
        if (!mapObject.isRigid()) {
            Floor *floor = new Floor(engine(), false, _spritesHandler);
            floor->x( x * 48 );
            floor->y( y * 48 );
            addObject(0, floor);
        }

        Wall *wall = new Wall(engine(), this, x, y,
                    mapObject.isRigid(), _spritesHandler,
                    mapObject.plateMaterial(MapObject::North),
                    mapObject.plateMaterial(MapObject::South),
                    mapObject.plateMaterial(MapObject::East),
                    mapObject.plateMaterial(MapObject::West));
        _levelObjects.push_back(wall);
        addObject(1, wall);
    }
}

void GameRoom::onStep()
{
    //int before = QTime::currentTime().msec();

    int x, y;
    LevelObject * currentObject;
    LevelObject * northObject;
    LevelObject * southObject;
    LevelObject * eastObject;
    LevelObject * westObject;
    std::vector<LevelObject*>::iterator it;

    for (it = _levelObjects.begin(); it != _levelObjects.end(); ++it) {
        (*it)->onStep();
    }

    bool done = false;
    while(!done) {
        done = true;
        for (it = _levelObjects.begin(); it != _levelObjects.end(); ++it) {
            currentObject = *it;

            if (currentObject->connected()) continue;
            if (currentObject->state() == LevelObject::MOVING) continue;

            x = currentObject->toX();
            y = currentObject->toY();

            northObject = levelObjectAt(x, y-1);
            southObject = levelObjectAt(x, y+1);
            eastObject = levelObjectAt(x+1, y);
            westObject = levelObjectAt(x-1, y);

            if (northObject != NULL && hasAttraction(northObject->southMaterial(), currentObject->northMaterial())) {
                currentObject->connected(true);
                northObject->connected(true);
                done = false;
            }

            else if (southObject != NULL && hasAttraction(southObject->northMaterial(), currentObject->southMaterial())) {
                currentObject->connected(true);
                southObject->connected(true);
                done = false;
            }

            else if (eastObject != NULL && hasAttraction(eastObject->westMaterial(), currentObject->eastMaterial())) {
                currentObject->connected(true);
                eastObject->connected(true);
                done = false;
            }

            else if (westObject != NULL && hasAttraction(westObject->eastMaterial(), currentObject->westMaterial())) {
                currentObject->connected(true);
                westObject->connected(true);
                done = false;
            }

            else if (currentObject->rigid()) {
                continue;
            }

            else if (northObject == NULL && southObject != NULL && southObject->idle() && hasRepulsion(southObject->northMaterial(), currentObject->southMaterial())) {
                currentObject->movingTo(x, y-1);
                if (southObject != NULL && southObject->canMove() && y+2 < _height && levelObjectAt(x, y+2) == NULL && hasRepulsion(southObject->northMaterial(), currentObject->southMaterial())) southObject->movingTo(x, y+2);
                if (northObject != NULL && northObject->canMove() && y-2 >= 0 && levelObjectAt(x, y-2) == NULL && hasRepulsion(northObject->southMaterial(), currentObject->northMaterial())) northObject->movingTo(x, y-2);
                if (westObject != NULL && westObject->canMove() && x-2 >= 0 && levelObjectAt(x-2, y) == NULL && hasRepulsion(westObject->eastMaterial(), currentObject->westMaterial())) westObject->movingTo(x-2, y);
                if (eastObject != NULL && eastObject->canMove() && x+2 < _width && levelObjectAt(x+2, y) == NULL && hasRepulsion(eastObject->westMaterial(), currentObject->eastMaterial())) eastObject->movingTo(x+2, y);
                done = false;
            }

            else if (southObject == NULL && northObject != NULL && northObject->idle() && hasRepulsion(northObject->southMaterial(), currentObject->northMaterial())) {
                currentObject->movingTo(x, y+1);
                if (southObject != NULL && southObject->canMove() && y+2 < _height && levelObjectAt(x, y+2) == NULL && hasRepulsion(southObject->northMaterial(), currentObject->southMaterial())) southObject->movingTo(x, y+2);
                if (northObject != NULL && northObject->canMove() && y-2 >= 0 && levelObjectAt(x, y-2) == NULL && hasRepulsion(northObject->southMaterial(), currentObject->northMaterial())) northObject->movingTo(x, y-2);
                if (westObject != NULL && westObject->canMove() && x-2 >= 0 && levelObjectAt(x-2, y) == NULL && hasRepulsion(westObject->eastMaterial(), currentObject->westMaterial())) westObject->movingTo(x-2, y);
                if (eastObject != NULL && eastObject->canMove() && x+2 < _width && levelObjectAt(x+2, y) == NULL && hasRepulsion(eastObject->westMaterial(), currentObject->eastMaterial())) eastObject->movingTo(x+2, y);
                done = false;
            }

            else if (eastObject == NULL && westObject != NULL && westObject->idle() && hasRepulsion(westObject->eastMaterial(), currentObject->westMaterial())) {
                currentObject->movingTo(x+1, y);
                if (southObject != NULL && southObject->canMove() && y+2 < _height && levelObjectAt(x, y+2) == NULL && hasRepulsion(southObject->northMaterial(), currentObject->southMaterial())) southObject->movingTo(x, y+2);
                if (northObject != NULL && northObject->canMove() && y-2 >= 0 && levelObjectAt(x, y-2) == NULL && hasRepulsion(northObject->southMaterial(), currentObject->northMaterial())) northObject->movingTo(x, y-2);
                if (westObject != NULL && westObject->canMove() && x-2 >= 0 && levelObjectAt(x-2, y) == NULL && hasRepulsion(westObject->eastMaterial(), currentObject->westMaterial())) westObject->movingTo(x-2, y);
                if (eastObject != NULL && eastObject->canMove() && x+2 < _width && levelObjectAt(x+2, y) == NULL && hasRepulsion(eastObject->westMaterial(), currentObject->eastMaterial())) eastObject->movingTo(x+2, y);
                done = false;
            }

            else if (westObject == NULL && eastObject != NULL && eastObject->idle() && hasRepulsion(eastObject->westMaterial(), currentObject->eastMaterial())) {
                currentObject->movingTo(x-1, y);
                if (southObject != NULL && southObject->canMove() && y+2 < _height && levelObjectAt(x, y+2) == NULL && hasRepulsion(southObject->northMaterial(), currentObject->southMaterial())) southObject->movingTo(x, y+2);
                if (northObject != NULL && northObject->canMove() && y-2 >= 0 && levelObjectAt(x, y-2) == NULL && hasRepulsion(northObject->southMaterial(), currentObject->northMaterial())) northObject->movingTo(x, y-2);
                if (westObject != NULL && westObject->canMove() && x-2 >= 0 && levelObjectAt(x-2, y) == NULL && hasRepulsion(westObject->eastMaterial(), currentObject->westMaterial())) westObject->movingTo(x-2, y);
                if (eastObject != NULL && eastObject->canMove() && x+2 < _width && levelObjectAt(x+2, y) == NULL && hasRepulsion(eastObject->westMaterial(), currentObject->eastMaterial())) eastObject->movingTo(x+2, y);
                done = false;
            }

            else if (!currentObject->hasPreferredDirection()) {
                continue;
            }

            else if (currentObject->preferredDirection() == MapObject::North) {
                if (northObject == NULL) {
                    levelObjectAt(x, y)->movingTo(x, y-1);
                    done = false;
                }
                else if (northObject->canMove() && !northObject->moving() && y - 2 >= 0 && levelObjectAt(x, y-2) == NULL) {
                    levelObjectAt(x, y-1)->movingTo(x, y-2);
                    levelObjectAt(x, y)->movingTo(x, y-1);
                    done = false;
                }
            }

            else if (currentObject->preferredDirection() == MapObject::South) {
                if (southObject == NULL) {
                    levelObjectAt(x, y)->movingTo(x, y+1);
                    done = false;
                }
                else if (southObject->canMove() && !southObject->moving() && y + 2 < _height && levelObjectAt(x, y+2) == NULL) {
                    levelObjectAt(x, y+1)->movingTo(x, y+2);
                    levelObjectAt(x, y)->movingTo(x, y+1);
                    done = false;
                }
            }

            else if (currentObject->preferredDirection() == MapObject::East) {
                if (eastObject == NULL) {
                    levelObjectAt(x, y)->movingTo(x+1, y);
                    done = false;
                }
                else if (eastObject->canMove() && !eastObject->moving() && x + 2 < _width && levelObjectAt(x+2, y) == NULL) {
                    levelObjectAt(x+1, y)->movingTo(x+2, y);
                    levelObjectAt(x, y)->movingTo(x+1, y);
                    done = false;
                }
            }

            else if (currentObject->preferredDirection() == MapObject::West) {
                if (westObject == NULL) {
                    levelObjectAt(x, y)->movingTo(x-1, y);
                    done = false;
                }
                else if (westObject->canMove() && !westObject->moving() && x - 2 >= 0 && levelObjectAt(x-2, y) == NULL) {
                    levelObjectAt(x-1, y)->movingTo(x-2, y);
                    levelObjectAt(x, y)->movingTo(x-1, y);
                    done = false;
                }
            }
        }
    }

    unsigned int objectivesWithBox = 0;
    for (it = _levelObjects.begin(); it != _levelObjects.end(); ++it) {
        if ((*it)->canConnectToObjective() && (*it)->idle() && isObjective((*it)->toX(), (*it)->toY()))
            ++objectivesWithBox;
    }

    if (objectivesWithBox == _objectives.size()) {

        Map *map = _mapPack->at(_level);

        int robotMoves = _robot == NULL ? 0 : _robot->moves();
        int gold = map->stepsForGold();
        int silver = map->stepsForSilver();
        int bronze = map->stepsForBronze();

        if (robotMoves <= gold)
            _gameProgress->putStar(GameProgress::GOLD, _level);
        else if (robotMoves <= silver)
            _gameProgress->putStar(GameProgress::SILVER, _level);
        else if (robotMoves <= bronze)
            _gameProgress->putStar(GameProgress::BRONZE, _level);
        else
            _gameProgress->putStar(GameProgress::MISSING, _level);

        _finishLevelRoom->steps(robotMoves, gold, silver, bronze);
        modal(_finishLevelRoom);
    }

    //int after = QTime::currentTime().msec();

    //if (after < before) after += 1000;
    //std::cout << after-before << std::endl;
}

bool GameRoom::hasRepulsion(MapObject::Material m1, MapObject::Material m2)
{
    return m1 == m2 && (m1 == MapObject::MagneticNorth || m1 == MapObject::MagneticSouth);
}

bool GameRoom::hasAttraction(MapObject::Material m1, MapObject::Material m2)
{
    return ( (m1 == MapObject::MagneticNorth && m2 == MapObject::MagneticSouth)
             || (m1 == MapObject::MagneticSouth && m2 == MapObject::MagneticNorth)
             || (m1 == MapObject::MagneticNorth && m2 == MapObject::Metal)
             || (m1 == MapObject::Metal && m2 == MapObject::MagneticNorth)
             || (m1 == MapObject::MagneticSouth && m2 == MapObject::Metal)
             || (m1 == MapObject::Metal && m2 == MapObject::MagneticSouth) );
}

LevelObject * GameRoom::levelObjectAt(const int x, const int y)
{
    std::vector<LevelObject*>::iterator it;

    for (it = _levelObjects.begin(); it != _levelObjects.end(); ++it) {
        if ( ((*it)->toX() == x && (*it)->toY() == y) /*|| ((*it)->fromX() == x && (*it)->fromY() == y)*/ )
            return (*it);
    }
    return NULL;
}

int GameRoom::width()
{
    return _width;
}

int GameRoom::height()
{
    return _height;
}

bool GameRoom::isObjective(const int x, const int y)
{
    return _objectives.find(y * _width + x) != _objectives.end();
}

void GameRoom::onKeyRelease(KeyListener::Key key)
{
    if (key == KeyListener::Escape) {
        Map *map = _mapPack->at(_level);

        int robotMoves = _robot == NULL ? 0 : _robot->moves();
        int gold = map->stepsForGold();
        int silver = map->stepsForSilver();
        int bronze = map->stepsForBronze();

        _pauseRoom->steps(robotMoves, gold, silver, bronze);
        modal(_pauseRoom);
    }
}

void GameRoom::onModalRoomClose(Room *modalRoom, int resultCode)
{
    if (modalRoom == _pauseRoom) {
        switch(resultCode) {
        case ModalRoomPause::RESULT_MENU: engine()->goTo(_previousRoom); break;
        case ModalRoomPause::RESULT_RESTART: engine()->goTo(this); break;
        case ModalRoomPause::RESULT_RESUME: break;
        }
    }

    else if (modalRoom == _finishLevelRoom) {
        switch(resultCode) {
        case ModalRoomFinishLevel::RESULT_MENU: engine()->goTo(_previousRoom); break;
        case ModalRoomFinishLevel::RESULT_RESTART: engine()->goTo(this); break;
        case ModalRoomFinishLevel::RESULT_NEXT:

            if (++_level < (int)_mapPack->all()->size())
                engine()->goTo(this);
            else
                engine()->goTo(_previousRoom);

            break;
        }
    }
}

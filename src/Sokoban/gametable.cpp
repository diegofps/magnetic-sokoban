#include "gametable.h"
#include "map.h"
#include "gameroom.h"
#include "sprite.h"
#include "floor.h"

GameTable::GameTable(Engine * engine, GameRoom *gameRoom, Map * map, SpritesHandler *spritesHandler) :
    Object(engine), _gameRoom(gameRoom), _spritesHandler(spritesHandler)
{
    createTable(map);
    _gameRoom->addKeyListener(this);
    _gameRoom->addStepListener(this);
    //_gameRoom->setViewportRefresher(this);
}

void GameTable::createTable(Map *map)
{
    _width = map->width();
    _height = map->height();
    _table = new LevelObject[_width * _height];

    int x, y;
    for (y = 0; y < _height; ++y)
        for (x = 0; x < _width; ++x)
            createLevelObject(_table[y * _width + x], map->at(x, y), x, y);
}

void GameTable::createLevelObject(LevelObject & levelObject, const MapObject & mapObject, const int x, const int y)
{
    if (mapObject.type() == MapObject::Floor) {
        Floor *floor = new Floor(engine(), mapObject.isObjective(), _spritesHandler);
        floor->x( x * 48 );
        floor->y( y * 48 );
        _gameRoom->addObject(floor);
        levelObject.isObjective(mapObject.isObjective());
        levelObject.isOrig(true);
    }

    else if (mapObject.type() == MapObject::Robot) {
        Floor *floor = new Floor(engine(), false, _spritesHandler);
        floor->x( x * 48 );
        floor->y( y * 48 );
        _gameRoom->addObject(floor);

        levelObject.gazeDirection(mapObject.direction());
        levelObject.isRobot(true);
        levelObject.isOrig(true);
        levelObject.isEmpty(false);
        _robotIndex = y * _width + x;

        switch(mapObject.direction()) {
        case MapObject::North: levelObject.sprite(_spritesHandler->robotNorth()); break;
        case MapObject::South: levelObject.sprite(_spritesHandler->robotSouth()); break;
        case MapObject::East: levelObject.sprite(_spritesHandler->robotEast()); break;
        default: levelObject.sprite(_spritesHandler->robotWest()); break;
        }

        _levelObjects.insert(std::pair<int, LevelObject*>(_robotIndex, &levelObject));
    }

    else if (mapObject.type() == MapObject::Wall) {
        levelObject.north(mapObject.plateMaterial(MapObject::North));
        levelObject.south(mapObject.plateMaterial(MapObject::South));
        levelObject.east (mapObject.plateMaterial(MapObject::East ));
        levelObject.west (mapObject.plateMaterial(MapObject::West ));
        levelObject.isMovable(!mapObject.isRigid());
        levelObject.isOrig(true);
        levelObject.isEmpty(false);

        if (levelObject.isMovable()) {
            levelObject.sprite(_spritesHandler->movableWall());

            Floor *floor = new Floor(engine(), false, _spritesHandler);
            floor->x( x * 48 );
            floor->y( y * 48 );
            _gameRoom->addObject(floor);
        }
        else {
            levelObject.sprite(_spritesHandler->rigidWall());
        }

        _levelObjects.insert(std::pair<int, LevelObject*>(y * _width + x, &levelObject));
    }
}

void GameTable::onStep()
{
    // Connect compatible boxes and repell incompatibles
    int x, y;
    LevelObject *currentObject;
    std::map<int, LevelObject*>::iterator it;
    for (it = _levelObjects.begin(); it != _levelObjects.end(); ++it) {
        x = (*it).first % _width;
        y = (*it).first / _width;
        currentObject = (*it).second;

        if (currentObject->isBind()) continue;

        LevelObject &northNeighbor = _table[(y - 1) * _width + (x    )];
        LevelObject &southNeighbor = _table[(y + 1) * _width + (x    )];
        LevelObject &eastNeighbor  = _table[(y    ) * _width + (x + 1)];
        LevelObject &westNeighbor  = _table[(y    ) * _width + (x - 1)];

        // Bind compatibles
        if (    (!eastNeighbor.isEmpty () && hasAttraction(currentObject->east() , eastNeighbor.west()   ))
             || (!southNeighbor.isEmpty() && hasAttraction(currentObject->south(), southNeighbor.north() ))
             || (!westNeighbor.isEmpty () && hasAttraction(currentObject->west() , westNeighbor.east()   ))
             || (!northNeighbor.isEmpty() && hasAttraction(currentObject->north(), northNeighbor.south() )) )
        {
            currentObject->isBind(true);
            currentObject->isMovable(false);
            currentObject->sprite(_spritesHandler->bindedWall());
        }

        // Repell incompatibles
        else if (currentObject->isMovable() && !currentObject->isMoving()
                 && eastNeighbor.isEmpty() && !westNeighbor.isEmpty() && !westNeighbor.isMoving()
                 && hasRepulsion(currentObject->west(), westNeighbor.east())) {
            currentObject->movingDirection(MapObject::East);
            eastNeighbor.movingDirection(MapObject::East);
        }

        else if (currentObject->isMovable() && !currentObject->isMoving()
                 && southNeighbor.isEmpty() && !northNeighbor.isEmpty() && !northNeighbor.isMoving()
                 && hasRepulsion(currentObject->north(), northNeighbor.south())) {
            currentObject->movingDirection(MapObject::South);
            southNeighbor.movingDirection(MapObject::South);
        }

        else if (currentObject->isMovable() && !currentObject->isMoving()
                 && westNeighbor.isEmpty() && !eastNeighbor.isEmpty() && !eastNeighbor.isMoving()
                 && hasRepulsion(currentObject->east(), eastNeighbor.west())) {
            currentObject->movingDirection(MapObject::West);
            westNeighbor.movingDirection(MapObject::West);
        }

        else if (currentObject->isMovable() && !currentObject->isMoving()
                 && northNeighbor.isEmpty() && !southNeighbor.isEmpty() && !southNeighbor.isMoving()
                 && hasRepulsion(currentObject->south(), southNeighbor.north())) {
            currentObject->movingDirection(MapObject::North);
            northNeighbor.movingDirection(MapObject::North);
        }

    }

    LevelObject & robot = _table[_robotIndex];

    // Move the robot and it's box
    if (!robot.isMoving()) {

        int robotX = _robotIndex % _width;
        int robotY = _robotIndex / _width;

        if (_up) {
            robot.sprite(_spritesHandler->robotMoveNorth());

            LevelObject & northNeighbor = _table[(robotY - 1) * _width + (robotX)];

            if (northNeighbor.isEmpty()) {
                robot.movingDirection(MapObject::North);
                northNeighbor.movingDirection(MapObject::North);
            }

            else if (northNeighbor.isMovable() && !northNeighbor.isMoving() && robotY - 2 >= 0) {
                LevelObject & northNorthNeighbor = _table[(robotY - 2) * _width + (robotX)];

                if (northNorthNeighbor.isEmpty()){
                    northNorthNeighbor.movingDirection(MapObject::North);
                    northNeighbor.movingDirection(MapObject::North);
                    robot.movingDirection(MapObject::North);
                }
            }
        }

        else if (_down) {
            robot.sprite(_spritesHandler->robotMoveSouth());

            LevelObject & southNeighbor = _table[(robotY + 1) * _width + (robotX)];

            if (southNeighbor.isEmpty()) {
                robot.movingDirection(MapObject::South);
                southNeighbor.movingDirection(MapObject::South);
            }

            else if (southNeighbor.isMovable() && !southNeighbor.isMoving() && robotY + 2 < _height) {
                LevelObject & southSouthNeighbor = _table[(robotY + 2) * _width + (robotX)];

                if (southSouthNeighbor.isEmpty()){
                    southSouthNeighbor.movingDirection(MapObject::South);
                    southNeighbor.movingDirection(MapObject::South);
                    robot.movingDirection(MapObject::South);
                }
            }
        }

        else if (_right) {
            robot.sprite(_spritesHandler->robotMoveEast());

            LevelObject & eastNeighbor = _table[(robotY) * _width + (robotX + 1)];

            if (eastNeighbor.isEmpty()) {
                robot.movingDirection(MapObject::East);
                eastNeighbor.movingDirection(MapObject::East);
            }

            else if (eastNeighbor.isMovable() && !eastNeighbor.isMoving() && robotX + 2 < _width) {
                LevelObject & eastEastNeighbor = _table[(robotY) * _width + (robotX + 2)];

                if (eastEastNeighbor.isEmpty()){
                    eastEastNeighbor.movingDirection(MapObject::East);
                    eastNeighbor.movingDirection(MapObject::East);
                    robot.movingDirection(MapObject::East);
                }
            }
        }

        else if (_left) {
            robot.sprite(_spritesHandler->robotMoveWest());

            LevelObject & westNeighbor = _table[(robotY) * _width + (robotX - 1)];

            if (westNeighbor.isEmpty()) {
                robot.movingDirection(MapObject::West);
                westNeighbor.movingDirection(MapObject::West);
            }

            else if (westNeighbor.isMovable() && !westNeighbor.isMoving() && robotX - 2 >= 0) {
                LevelObject & westWestNeighbor = _table[(robotY) * _width + (robotX - 2)];

                if (westWestNeighbor.isEmpty()){
                    westWestNeighbor.movingDirection(MapObject::West);
                    westNeighbor.movingDirection(MapObject::West);
                    robot.movingDirection(MapObject::West);
                }
            }
        }

    }

}

void GameTable::draw(const Viewport &viewport, Graphics *g)
{
    int x, y;
    int drawX, drawY;
    float interpolation;
    LevelObject *currentObject;
    std::map<int, LevelObject*>::iterator it;

    for (it = _levelObjects.begin(); it != _levelObjects.end(); ++it) {
        x = (*it).first % _width;
        y = (*it).first / _width;
        currentObject = (*it).second;

        if (!currentObject->isOrig()) continue;

        drawX = x * 48;
        drawY = y * 48;

        if (currentObject->isAboutToMove())
            currentObject->isMoving(true);

        if (currentObject->isMoving()) {
            currentObject->incMovingFrame();

            interpolation = currentObject->movingFrameInterpolation();

            switch(currentObject->movingDirection()) {
            case MapObject::North: drawY -= (int)(48 * interpolation); break;
            case MapObject::South: drawY += (int)(48 * interpolation); break;
            case MapObject::East:  drawX += (int)(48 * interpolation); break;
            default:               drawX -= (int)(48 * interpolation); break;
            }

        }

        if (currentObject->isRobot())
            drawRobot(viewport, g, currentObject, drawX, drawY);
        else
            drawWall(viewport, g, currentObject, drawX, drawY);

    }

    for (it = _levelObjects.begin(); it != _levelObjects.end();) {
        x = (*it).first % _width;
        y = (*it).first / _width;
        currentObject = (*it).second;

        if (currentObject->atLastMovingFrame())
            finishMoving(currentObject, (*it).first, it);
        else
             ++it;
    }

}

void GameTable::finishMoving(LevelObject *currentObject, int index2, std::map<int, LevelObject*>::iterator &it)
{
    std::map<int, LevelObject*>::iterator itToDel;
    int x = index2 % _width;
    int y = index2 / _width;
    int index;

    switch(currentObject->movingDirection()) {
    case MapObject::North: index = (y - 1) * _width + (x); break;
    case MapObject::South: index = (y + 1) * _width + (x); break;
    case MapObject::East: index = (y) * _width + (x + 1); break;
    default: index = (y) * _width + (x - 1); break;
    }

    if (_table[index].atLastMovingFrame())
        finishMoving(&_table[index], index, it);

    _table[index].isOrig(true);
    _table[index].north(currentObject->north());
    _table[index].south(currentObject->south());
    _table[index].east(currentObject->east());
    _table[index].west(currentObject->west());
    _table[index].isRobot(currentObject->isRobot());
    _table[index].isMovable(currentObject->isMovable());
    _table[index].isEmpty(currentObject->isEmpty());
    _table[index].sprite(currentObject->sprite());
    _table[index].isMoving(false);

    currentObject->isEmpty(true);
    currentObject->isOrig(false);
    currentObject->isMovable(false);
    currentObject->isMoving(false);

    if (!_table[index].isRobot()) {
        if (_table[index].isObjective() && !_table[index].isRobot())
            _table[index].sprite(_spritesHandler->atObjectiveWall());
        else
            _table[index].sprite(_spritesHandler->movableWall());
    }

    itToDel = it;
    ++it;
    _levelObjects.erase(itToDel);
    _levelObjects.insert(std::pair<int, LevelObject*>(index, &_table[index]));

    if (_robotIndex == (y * _width + x))
        _robotIndex = index;
}

void GameTable::drawRobot(const Viewport &v, Graphics *g, LevelObject * obj, const int drawX, const int drawY)
{
    if (obj->sprite() != NULL)
        obj->sprite()->draw(g, drawX - v.x(), drawY - v.y());
}

void GameTable::drawWall(const Viewport &v, Graphics *g, LevelObject * obj, int drawX, int drawY)
{
    drawX = drawX - v.x();
    drawY = drawY - v.y();

    if (obj->sprite() != NULL)
        obj->sprite()->draw(g, drawX, drawY);

    switch(obj->north()) {
    case MapObject::MagneticNorth: _spritesHandler->plateMagneticNorthNorth()->draw(g, drawX, drawY); break;
    case MapObject::MagneticSouth: _spritesHandler->plateMagneticSouthNorth()->draw(g, drawX, drawY); break;
    case MapObject::Metal: _spritesHandler->plateMetalNorth()->draw(g, drawX, drawY); break;
    default: break;
    }

    switch(obj->south()) {
    case MapObject::MagneticNorth: _spritesHandler->plateMagneticNorthSouth()->draw(g, drawX, drawY); break;
    case MapObject::MagneticSouth: _spritesHandler->plateMagneticSouthSouth()->draw(g, drawX, drawY); break;
    case MapObject::Metal: _spritesHandler->plateMetalSouth()->draw(g, drawX, drawY); break;
    default: break;
    }

    switch(obj->east()) {
    case MapObject::MagneticNorth: _spritesHandler->plateMagneticNorthEast()->draw(g, drawX, drawY); break;
    case MapObject::MagneticSouth: _spritesHandler->plateMagneticSouthEast()->draw(g, drawX, drawY); break;
    case MapObject::Metal: _spritesHandler->plateMetalEast()->draw(g, drawX, drawY); break;
    default: break;
    }

    switch(obj->west()) {
    case MapObject::MagneticNorth: _spritesHandler->plateMagneticNorthWest()->draw(g, drawX, drawY); break;
    case MapObject::MagneticSouth: _spritesHandler->plateMagneticSouthWest()->draw(g, drawX, drawY); break;
    case MapObject::Metal: _spritesHandler->plateMetalWest()->draw(g, drawX, drawY); break;
    default: break;
    }
}

bool GameTable::hasRepulsion(MapObject::Material m1, MapObject::Material m2)
{
    return m1 == m2 && (m1 == MapObject::MagneticNorth || m1 == MapObject::MagneticSouth);
}

bool GameTable::hasAttraction(MapObject::Material m1, MapObject::Material m2)
{
    return ( (m1 == MapObject::MagneticNorth && m2 == MapObject::MagneticSouth)
             || (m1 == MapObject::MagneticSouth && m2 == MapObject::MagneticNorth)
             || (m1 == MapObject::MagneticNorth && m2 == MapObject::Metal)
             || (m1 == MapObject::Metal && m2 == MapObject::MagneticNorth)
             || (m1 == MapObject::MagneticSouth && m2 == MapObject::Metal)
             || (m1 == MapObject::Metal && m2 == MapObject::MagneticSouth) );
}

void GameTable::onKeyPress(KeyListener::Key key)
{
    if (key == KeyListener::Left) _left = true;
    if (key == KeyListener::Right) _right = true;
    if (key == KeyListener::Up) _up = true;
    if (key == KeyListener::Down) _down = true;
}

void GameTable::onKeyRelease(KeyListener::Key key)
{
    if (key == KeyListener::Left) _left = false;
    if (key == KeyListener::Right) _right = false;
    if (key == KeyListener::Up) _up = false;
    if (key == KeyListener::Down) _down = false;
}

#include "levelobject.h"

LevelObject::LevelObject(Engine *engine, const int x, const int y) :
    Object(engine), _frame(0), _state(IDLE), _rigid(false),
    _connected(false), _toX(x), _toY(y), _fromX(x), _fromY(y),
    _hasPreferredDirection(false), _moves(0), _canConnectToObjective(true)
{
    this->x( x * 48 );
    this->y( y * 48 );
}

void LevelObject::onStep()
{
    if (state() == MOVING) {
        _frame += 1;

        x( (_frame * (_toX - _fromX) + ANIM_STEPS * _fromX) / (float)ANIM_STEPS * 48 );
        y( (_frame * (_toY - _fromY) + ANIM_STEPS * _fromY) / (float)ANIM_STEPS * 48 );

        if (_frame >= ANIM_STEPS) {
            _fromX = _toX;
            _fromY = _toY;
            _frame = 0;
            _hasPreferredDirection = false;
            state(IDLE);
            onFinishMove();
            onIdle();
        }
    }
    else {
        onIdle();
    }
}

void LevelObject::movingTo(int toX, int toY)
{
    ++_moves;
    state(MOVING);

    _hasPreferredDirection = false;
    _fromX = _toX;
    _fromY = _toY;
    _toX = toX;
    _toY = toY;
}

bool LevelObject::moving()
{
    return state() == MOVING;
}

bool LevelObject::idle()
{
    return state() == IDLE;
}

void LevelObject::state(int state)
{
    _state = state;
}

int LevelObject::state()
{
    return _state;
}

float LevelObject::interpolation()
{
    return (float)_frame / ANIM_STEPS;
}

void LevelObject::rigid(bool rigid)
{
    _rigid = rigid;
}

bool LevelObject::rigid()
{
    return _rigid;
}

void LevelObject::move(MapObject::Direction direction)
{
    _hasPreferredDirection = true;
    _preferredDirection = direction;
}

void LevelObject::northMaterial(MapObject::Material material)
{
    _north = material;
}

void LevelObject::southMaterial(MapObject::Material material)
{
    _south = material;
}

void LevelObject::eastMaterial(MapObject::Material material)
{
    _east = material;
}

void LevelObject::westMaterial(MapObject::Material material)
{
    _west = material;
}

MapObject::Material LevelObject::northMaterial()
{
    return _north;
}

MapObject::Material LevelObject::southMaterial()
{
    return _south;
}

MapObject::Material LevelObject::eastMaterial()
{
    return _east;
}

MapObject::Material LevelObject::westMaterial()
{
    return _west;
}

void LevelObject::connected(bool connected)
{
    _connected = connected;
}

bool LevelObject::connected()
{
    return _connected;
}

bool LevelObject::hasPreferredDirection()
{
    return _hasPreferredDirection;
}

MapObject::Direction LevelObject::preferredDirection()
{
    return _preferredDirection;
}

int LevelObject::toX()
{
    return _toX;
}

int LevelObject::toY()
{
    return _toY;
}

int LevelObject::fromX()
{
    return _fromX;
}

int LevelObject::fromY()
{
    return _fromY;
}

bool LevelObject::canMove()
{
    return !rigid() && !connected();
}

int LevelObject::moves()
{
    return _moves;
}

bool LevelObject::canConnectToObjective()
{
    return _canConnectToObjective;
}

void LevelObject::canConnectToObjective(bool canConnectToObjective)
{
    _canConnectToObjective = canConnectToObjective;
}

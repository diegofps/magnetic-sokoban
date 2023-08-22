#ifndef LEVELOBJECT_H
#define LEVELOBJECT_H

#include "object.h"
#include "mapobject.h"
#include "steplistener.h"

class LevelObject : public Object, public StepListener
{

private:

    static const int ANIM_STEPS = 11;

    static const int IDLE = 0;

    static const int MOVING = 1;

private:

    friend class GameRoom;

    void state(int state);

    void movingTo(int toX, int toY);

    bool hasPreferredDirection();

    MapObject::Direction preferredDirection();

public:

    LevelObject(Engine *engine, const int x, const int y);

    int state();

    float interpolation();

    void rigid(bool rigid);

    void move(MapObject::Direction direction);

    void northMaterial(MapObject::Material material);

    void southMaterial(MapObject::Material material);

    void eastMaterial(MapObject::Material material);

    void westMaterial(MapObject::Material material);

    void connected(bool connected);

    void canConnectToObjective(bool canConnectToObjective);


    bool rigid();

    MapObject::Material northMaterial();

    MapObject::Material southMaterial();

    MapObject::Material eastMaterial();

    MapObject::Material westMaterial();

    bool connected();

    bool canConnectToObjective();

    int toX();

    int toY();

    int fromX();

    int fromY();

    bool moving();

    bool idle();

    bool canMove();

    int moves();


    virtual void onStep();

    virtual void onIdle() = 0;

    virtual void onFinishMove() = 0;


private:

    int _frame;

    int _state;

    bool _rigid;

    bool _connected;

    MapObject::Direction _preferredDirection;

    MapObject::Material _north;

    MapObject::Material _south;

    MapObject::Material _east;

    MapObject::Material _west;

    int _toX;

    int _toY;

    int _fromX;

    int _fromY;

    bool _hasPreferredDirection;

    int _moves;

    bool _canConnectToObjective;

};

#endif // LEVELOBJECT_H

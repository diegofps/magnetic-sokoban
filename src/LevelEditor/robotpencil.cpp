#include "robotpencil.h"

RobotPencil::RobotPencil(const QPixmap & pixmap, MapObject::Direction direction) :
    MapPencil(pixmap),
    _direction(direction)
{

}

QString RobotPencil::name() const
{
    switch(_direction) {
    case MapObject::North: return "Robot North";
    case MapObject::South: return "Robot South";
    case MapObject::East: return "Robot East";
    default: return "Robot West";
    }
}

MapObject RobotPencil::paint(const MapObject &) const
{
    MapObject mapObject;
    mapObject.type(MapObject::Robot);
    mapObject.direction(_direction);
    return mapObject;
}

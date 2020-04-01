#include "mapobject.h"

MapObject::MapObject() : _type(MapObject::None)
{

}

MapObject::Type MapObject::type() const
{
    return _type;
}

MapObject::Direction MapObject::direction() const
{
    return _direction;
}

MapObject::Material MapObject::plateMaterial(const MapObject::Direction direction) const
{
    switch(direction) {
    case MapObject::North: return _plateNorth;
    case MapObject::South: return _plateSouth;
    case MapObject::East: return _plateEast;
    default: return _plateWest;
    }
}

bool MapObject::isRigid() const
{
    return _isRigid;
}

bool MapObject::isObjective() const
{
    return _isObjective;
}


void MapObject::type(const MapObject::Type type)
{
    _type = type;
}

void MapObject::direction(const MapObject::Direction direction)
{
    _direction = direction;
}

void MapObject::plateMaterial(const MapObject::Direction direction, const MapObject::Material material)
{
    switch(direction) {
    case MapObject::North: _plateNorth = material; break;
    case MapObject::South: _plateSouth = material; break;
    case MapObject::East: _plateEast = material; break;
    default: _plateWest = material; break;
    }
}

void MapObject::isRigid(const bool isRigid)
{
    _isRigid = isRigid;
}

void MapObject::isObjective(const bool isObjective)
{
    _isObjective = isObjective;
}

bool MapObject::operator !=(const MapObject &other)
{
    return !((*this) == other);
}

bool MapObject::operator ==(const MapObject &other)
{
    if (type() != other.type()) return false;

    switch(type()) {

    case MapObject::Floor:
        return isObjective() == other.isObjective();

    case MapObject::Robot:
        return direction() == other.direction();

    case MapObject::Wall:
        return plateMaterial(MapObject::North) == other.plateMaterial(MapObject::North)
                && plateMaterial(MapObject::South) == other.plateMaterial(MapObject::South)
                && plateMaterial(MapObject::East) == other.plateMaterial(MapObject::East)
                && plateMaterial(MapObject::West) == other.plateMaterial(MapObject::West)
                && isRigid() == other.isRigid();

    default:
        return false;

    }
}

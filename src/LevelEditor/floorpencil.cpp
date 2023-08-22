#include "floorpencil.h"

FloorPencil::FloorPencil(const QPixmap &pixmap, bool isObjective) :
    MapPencil(pixmap),
    _isObjective(isObjective)
{

}

QString FloorPencil::name() const
{
    if (_isObjective)
        return "Floor Objective";
    else
        return "Floor";
}

MapObject FloorPencil::paint(const MapObject &) const
{
    MapObject mapObject;
    mapObject.type(MapObject::Floor);
    mapObject.isObjective(_isObjective);
    return mapObject;
}

#include "rigidpencil.h"

RigidPencil::RigidPencil(const QPixmap & pixmap, bool isRigid) :
    MapPencil(pixmap),
    _isRigid(isRigid)
{

}

QString RigidPencil::name() const
{
    if (_isRigid)
        return "Convert to Rigid Wall";
    else
        return "Convert to Movebla Wall";
}

MapObject RigidPencil::paint(const MapObject &mapObject) const
{
    MapObject result(mapObject);

    if (result.type() != MapObject::Wall) {
        result.type(MapObject::Wall);
        result.plateMaterial(MapObject::North, MapObject::Neutral);
        result.plateMaterial(MapObject::South, MapObject::Neutral);
        result.plateMaterial(MapObject::East, MapObject::Neutral);
        result.plateMaterial(MapObject::West, MapObject::Neutral);
    }

    result.isRigid(_isRigid);

    return result;
}


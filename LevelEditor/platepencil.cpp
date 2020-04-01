#include "platepencil.h"

PlatePencil::PlatePencil(const QPixmap & pixmap, MapObject::Material material, MapObject::Direction direction) :
    MapPencil(pixmap),
    _material(material), _direction(direction)
{

}

QString PlatePencil::name() const
{
    QString plate, material;

    switch(_direction) {
    case MapObject::North: plate = "North"; break;
    case MapObject::South: plate = "South"; break;
    case MapObject::East: plate = "East"; break;
    default: plate = "West"; break;
    }

    switch(_material) {
    case MapObject::MagneticNorth: material = "Magnetic North"; break;
    case MapObject::MagneticSouth: material = "Magnetic South"; break;
    case MapObject::Metal: material = "Metal"; break;
    default: material = "Neutral"; break;
    }

    return "Convert " + plate + " plate to " + material;
}

MapObject PlatePencil::paint(const MapObject &mapObject) const
{
    MapObject result(mapObject);

    if (result.type() != MapObject::Wall) {
        result.type(MapObject::Wall);
        result.plateMaterial(MapObject::North, MapObject::Neutral);
        result.plateMaterial(MapObject::South, MapObject::Neutral);
        result.plateMaterial(MapObject::East, MapObject::Neutral);
        result.plateMaterial(MapObject::West, MapObject::Neutral);
        result.isRigid(true);
    }

    result.plateMaterial(_direction, _material);

    return result;
}

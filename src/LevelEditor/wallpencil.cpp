#include "wallpencil.h"

WallPencil::WallPencil(const QPixmap & pixmap, const MapObject::Material material, bool isRigid) :
    MapPencil(pixmap),
    _material(material), _isRigid(isRigid)
{

}

QString WallPencil::name() const
{
    if (_isRigid) {
        switch(_material) {
        case MapObject::MagneticNorth: return "Rigid Magnetic North Wall";
        case MapObject::MagneticSouth: return "Rigid Magnetic South Wall";
        case MapObject::Metal: return "Rigid Metal Wall";
        default: return "Rigid Neutral Wall";
        }
    }
    else {
        switch(_material) {
        case MapObject::MagneticNorth: return "Movebla Magnetic North Wall";
        case MapObject::MagneticSouth: return "Movebla Magnetic South Wall";
        case MapObject::Metal: return "Movebla Metal Wall";
        default: return "Movebla Neutral Wall";
        }
    }
}

MapObject WallPencil::paint(const MapObject &) const
{
    MapObject result;
    result.type(MapObject::Wall);
    result.plateMaterial(MapObject::North, _material);
    result.plateMaterial(MapObject::South, _material);
    result.plateMaterial(MapObject::East, _material);
    result.plateMaterial(MapObject::West, _material);
    result.isRigid(_isRigid);
    return result;
}

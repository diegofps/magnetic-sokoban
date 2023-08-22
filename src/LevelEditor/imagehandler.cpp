#include "imagehandler.h"
#include "mapobject.h"
#include <QPainter>

ImageHandler::ImageHandler()
{
    _floor = new QPixmap(48,48);
    _floorObjective = new QPixmap(48,48);
    _robotNorth = new QPixmap(48,48);
    _robotSouth = new QPixmap(48,48);
    _robotEast = new QPixmap(48,48);
    _robotWest = new QPixmap(48,48);
    _wallMovebla = new QPixmap(48,48);
    _wallRigid = new QPixmap(48,48);
    _magneticNorthNorth = new QPixmap(48,48);
    _magneticNorthSouth = new QPixmap(48,48);
    _magneticNorthEast = new QPixmap(48,48);
    _magneticNorthWest = new QPixmap(48,48);
    _magneticSouthNorth = new QPixmap(48,48);
    _magneticSouthSouth = new QPixmap(48,48);
    _magneticSouthEast = new QPixmap(48,48);
    _magneticSouthWest = new QPixmap(48,48);
    _metalNorth = new QPixmap(48,48);
    _metalSouth = new QPixmap(48,48);
    _metalEast = new QPixmap(48,48);
    _metalWest = new QPixmap(48,48);
    _neutralNorth = new QPixmap(48,48);
    _neutralSouth = new QPixmap(48,48);
    _neutralEast = new QPixmap(48,48);
    _neutralWest = new QPixmap(48,48);
    _walls = new QPixmap*[4*4*4*4*2];

    for(int i=0;i<4*4*4*4*2;++i) _walls[i] = new QPixmap(48,48);

    _floor->load(":/icons/floor.svg");
    _wallMovebla->load(":icons/movableWallIcon.svg");
    _wallRigid->load(":icons/rigidWallIcon.svg");

    _magneticNorthNorth->load(":/icons/magneticNorthNorth.svg");
    _magneticNorthSouth->load(":/icons/magneticNorthSouth.svg");
    _magneticNorthEast->load(":/icons/magneticNorthEast.svg");
    _magneticNorthWest->load(":/icons/magneticNorthWest.svg");

    _magneticSouthNorth->load(":/icons/magneticSouthNorth.svg");
    _magneticSouthSouth->load(":/icons/magneticSouthSouth.svg");
    _magneticSouthEast->load(":/icons/magneticSouthEast.svg");
    _magneticSouthWest->load(":/icons/magneticSouthWest.svg");

    _metalNorth->load(":/icons/metalNorth.svg");
    _metalSouth->load(":/icons/metalSouth.svg");
    _metalEast->load(":/icons/metalEast.svg");
    _metalWest->load(":/icons/metalWest.svg");

    _neutralNorth->load(":/icons/neutralNorth.svg");
    _neutralSouth->load(":/icons/neutralSouth.svg");
    _neutralEast->load(":/icons/neutralEast.svg");
    _neutralWest->load(":/icons/neutralWest.svg");

    QPixmap objective; objective.load(":/icons/floorObjective.svg");
    QPixmap robotNorth; robotNorth.load(":/icons/robotNorth.svg");
    QPixmap robotSouth; robotSouth.load(":/icons/robotSouth.svg");
    QPixmap robotEast; robotEast.load(":/icons/robotEast.svg");
    QPixmap robotWest; robotWest.load(":/icons/robotWest.svg");
    QPixmap rigidWall; rigidWall.load(":/icons/rigidWall.svg");
    QPixmap moveblaWall; moveblaWall.load(":/icons/movableWall.svg");

    {
        QPainter painter(_floorObjective);
        painter.drawPixmap(0,0,*_floor);
        painter.drawPixmap(0,0,objective);
    }

    {
        QPainter painter(_robotNorth);
        painter.drawPixmap(0,0,*_floor);
        painter.drawPixmap(0,0,robotNorth);
    }

    {
        QPainter painter(_robotSouth);
        painter.drawPixmap(0,0,*_floor);
        painter.drawPixmap(0,0,robotSouth);
    }

    {
        QPainter painter(_robotEast);
        painter.drawPixmap(0,0,*_floor);
        painter.drawPixmap(0,0,robotEast);
    }

    {
        QPainter painter(_robotWest);
        painter.drawPixmap(0,0,*_floor);
        painter.drawPixmap(0,0,robotWest);
    }

    {
        QPainter painter(_robotWest);
        painter.drawPixmap(0,0,*_floor);
        painter.drawPixmap(0,0,robotWest);
    }

    {
        int index;
        int i,j,k,l,w;
        for (i=0;i<4;++i) {
            for (j=0;j<4;++j) {
                for (k=0;k<4;++k) {
                    for (l=0;l<4;++l) {
                        for (w=0;w<2;++w)
                        {
                            index = wallIndexFor(i,j,k,l,w);
                            QPainter painter(_walls[index]);

                            switch(w) {
                            case 0: painter.drawPixmap(0,0,moveblaWall); break;
                            default: painter.drawPixmap(0,0,rigidWall); break;
                            }

                            switch(i) {
                            case 0: painter.drawPixmap(0,0,*_magneticNorthNorth); break;
                            case 1: painter.drawPixmap(0,0,*_magneticSouthNorth); break;
                            case 2: painter.drawPixmap(0,0,*_metalNorth); break;
                            default: painter.drawPixmap(0,0,*_neutralNorth); break;
                            }

                            switch(j) {
                            case 0: painter.drawPixmap(0,0,*_magneticNorthSouth); break;
                            case 1: painter.drawPixmap(0,0,*_magneticSouthSouth); break;
                            case 2: painter.drawPixmap(0,0,*_metalSouth); break;
                            default: painter.drawPixmap(0,0,*_neutralSouth); break;
                            }

                            switch(k) {
                            case 0: painter.drawPixmap(0,0,*_magneticNorthEast); break;
                            case 1: painter.drawPixmap(0,0,*_magneticSouthEast); break;
                            case 2: painter.drawPixmap(0,0,*_metalEast); break;
                            default: painter.drawPixmap(0,0,*_neutralEast); break;
                            }

                            switch(l) {
                            case 0: painter.drawPixmap(0,0,*_magneticNorthWest); break;
                            case 1: painter.drawPixmap(0,0,*_magneticSouthWest); break;
                            case 2: painter.drawPixmap(0,0,*_metalWest); break;
                            default: painter.drawPixmap(0,0,*_neutralWest); break;
                            }

                        }
                    }
                }
            }
        }
    }

}

const QPixmap * ImageHandler::imageFor(const MapObject &mapObject) const
{
    int i,j,k,l,w;

    switch(mapObject.type()) {

    case MapObject::Floor:
        if (mapObject.isObjective())
            return _floorObjective;
        else
            return _floor;

    case MapObject::Robot:
        switch(mapObject.direction()) {
        case MapObject::North: return _robotNorth;
        case MapObject::South: return _robotSouth;
        case MapObject::East: return _robotEast;
        default: return _robotWest;
        }

    case MapObject::Wall:
        i = material2index(mapObject.plateMaterial(MapObject::North));
        j = material2index(mapObject.plateMaterial(MapObject::South));
        k = material2index(mapObject.plateMaterial(MapObject::East));
        l = material2index(mapObject.plateMaterial(MapObject::West));
        w = rigid2index(mapObject.isRigid());
        return _walls[wallIndexFor(i, j, k, l, w)];

    default:
        return NULL;

    }
}

const QPixmap & ImageHandler::floor() const
{
    return *_floor;
}

const QPixmap & ImageHandler::floorObjective() const
{
    return *_floorObjective;
}

const QPixmap & ImageHandler::robotNorth() const
{
    return *_robotNorth;
}

const QPixmap & ImageHandler::robotSouth() const
{
    return *_robotSouth;
}

const QPixmap & ImageHandler::robotEast() const
{
    return *_robotEast;
}

const QPixmap & ImageHandler::robotWest() const
{
    return *_robotWest;
}

const QPixmap & ImageHandler::wallRigid() const
{
    return *_wallRigid;
}

const QPixmap & ImageHandler::wallMovebla() const
{
    return *_wallMovebla;
}

const QPixmap & ImageHandler::magneticNorthNorth() const
{
    return *_magneticNorthNorth;
}

const QPixmap & ImageHandler::magneticNorthSouth() const
{
    return *_magneticNorthSouth;
}

const QPixmap & ImageHandler::magneticNorthEast() const
{
    return *_magneticNorthEast;
}

const QPixmap & ImageHandler::magneticNorthWest() const
{
    return *_magneticNorthWest;
}

const QPixmap & ImageHandler::magneticSouthNorth() const
{
    return *_magneticSouthNorth;
}

const QPixmap & ImageHandler::magneticSouthSouth() const
{
    return *_magneticSouthSouth;
}

const QPixmap & ImageHandler::magneticSouthEast() const
{
    return *_magneticSouthEast;
}

const QPixmap & ImageHandler::magneticSouthWest() const
{
    return *_magneticSouthWest;
}

const QPixmap & ImageHandler::metalNorth() const
{
    return *_metalNorth;
}

const QPixmap & ImageHandler::metalSouth() const
{
    return *_metalSouth;
}

const QPixmap & ImageHandler::metalEast() const
{
    return *_metalEast;
}

const QPixmap & ImageHandler::metalWest() const
{
    return *_metalWest;
}

const QPixmap & ImageHandler::neutralNorth() const
{
    return *_neutralNorth;
}

const QPixmap & ImageHandler::neutralSouth() const
{
    return *_neutralSouth;
}

const QPixmap & ImageHandler::neutralEast() const
{
    return *_neutralEast;
}

const QPixmap & ImageHandler::neutralWest() const
{
    return *_neutralWest;
}

const QPixmap & ImageHandler::wallMoveblaMagneticNorth() const
{
    int rigidIndex = rigid2index(false);
    int materialIndex = material2index(MapObject::MagneticNorth);
    return *_walls[wallIndexFor(materialIndex, materialIndex, materialIndex, materialIndex, rigidIndex)];
}

const QPixmap & ImageHandler::wallMoveblaMagneticSouth() const
{
    int rigidIndex = rigid2index(false);
    int materialIndex = material2index(MapObject::MagneticSouth);
    return *_walls[wallIndexFor(materialIndex, materialIndex, materialIndex, materialIndex, rigidIndex)];
}

const QPixmap & ImageHandler::wallMoveblaMetal() const
{
    int rigidIndex = rigid2index(false);
    int materialIndex = material2index(MapObject::Metal);
    return *_walls[wallIndexFor(materialIndex, materialIndex, materialIndex, materialIndex, rigidIndex)];
}

const QPixmap & ImageHandler::wallMoveblaNeutral() const
{
    int rigidIndex = rigid2index(false);
    int materialIndex = material2index(MapObject::Neutral);
    return *_walls[wallIndexFor(materialIndex, materialIndex, materialIndex, materialIndex, rigidIndex)];
}

const QPixmap & ImageHandler::wallRigidMagneticNorth() const
{
    int rigidIndex = rigid2index(true);
    int materialIndex = material2index(MapObject::MagneticNorth);
    return *_walls[wallIndexFor(materialIndex, materialIndex, materialIndex, materialIndex, rigidIndex)];
}

const QPixmap & ImageHandler::wallRigidMagneticSouth() const
{
    int rigidIndex = rigid2index(true);
    int materialIndex = material2index(MapObject::MagneticSouth);
    return *_walls[wallIndexFor(materialIndex, materialIndex, materialIndex, materialIndex, rigidIndex)];
}

const QPixmap & ImageHandler::wallRigidMetal() const
{
    int rigidIndex = rigid2index(true);
    int materialIndex = material2index(MapObject::Metal);
    return *_walls[wallIndexFor(materialIndex, materialIndex, materialIndex, materialIndex, rigidIndex)];
}

const QPixmap & ImageHandler::wallRigidNeutral() const
{
    int rigidIndex = rigid2index(true);
    int materialIndex = material2index(MapObject::Neutral);
    return *_walls[wallIndexFor(materialIndex, materialIndex, materialIndex, materialIndex, rigidIndex)];
}

int ImageHandler::wallIndexFor(const int i, const int j, const int k, const int l, const int w)
{
    int index = i;
    index = (index << 2) | j;
    index = (index << 2) | k;
    index = (index << 2) | l;
    index = (index << 1) | w;
    return index;
}

int ImageHandler::material2index(const MapObject::Material material)
{
    switch(material) {
    case MapObject::MagneticNorth: return 0;
    case MapObject::MagneticSouth: return 1;
    case MapObject::Metal: return 2;
    default: return 3;
    }
}

int ImageHandler::rigid2index(const bool rigid)
{
    return rigid ? 1 : 0;
}

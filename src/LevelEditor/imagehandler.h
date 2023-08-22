#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <QPixmap>
#include "mapobject.h"

class ImageHandler
{

public:

    ImageHandler();

    const QPixmap * imageFor(const MapObject & mapObject) const;

    const QPixmap & floor() const;

    const QPixmap & floorObjective() const;

    const QPixmap & robotNorth() const;

    const QPixmap & robotSouth() const;

    const QPixmap & robotEast() const;

    const QPixmap & robotWest() const;

    const QPixmap & wallRigid() const;

    const QPixmap & wallMovebla() const;

    const QPixmap & magneticNorthNorth() const;

    const QPixmap & magneticNorthSouth() const;

    const QPixmap & magneticNorthEast() const;

    const QPixmap & magneticNorthWest() const;

    const QPixmap & magneticSouthNorth() const;

    const QPixmap & magneticSouthSouth() const;

    const QPixmap & magneticSouthEast() const;

    const QPixmap & magneticSouthWest() const;

    const QPixmap & metalNorth() const;

    const QPixmap & metalSouth() const;

    const QPixmap & metalEast() const;

    const QPixmap & metalWest() const;

    const QPixmap & neutralNorth() const;

    const QPixmap & neutralSouth() const;

    const QPixmap & neutralEast() const;

    const QPixmap & neutralWest() const;

    const QPixmap & wallMoveblaMagneticNorth() const;

    const QPixmap & wallMoveblaMagneticSouth() const;

    const QPixmap & wallMoveblaMetal() const;

    const QPixmap & wallMoveblaNeutral() const;

    const QPixmap & wallRigidMagneticNorth() const;

    const QPixmap & wallRigidMagneticSouth() const;

    const QPixmap & wallRigidMetal() const;

    const QPixmap & wallRigidNeutral() const;

private:

    static int wallIndexFor(const int i, const int j, const int k, const int l, const int w);

    static int rigid2index(const bool rigid);

    static int material2index(const MapObject::Material material);

private:

    QPixmap * _floor;

    QPixmap * _floorObjective;

    QPixmap * _robotNorth;

    QPixmap * _robotSouth;

    QPixmap * _robotEast;

    QPixmap * _robotWest;

    QPixmap *_wallMovebla;

    QPixmap *_wallRigid;

    QPixmap *_magneticNorthNorth;

    QPixmap *_magneticNorthSouth;

    QPixmap *_magneticNorthEast;

    QPixmap *_magneticNorthWest;

    QPixmap *_magneticSouthNorth;

    QPixmap *_magneticSouthSouth;

    QPixmap *_magneticSouthEast;

    QPixmap *_magneticSouthWest;

    QPixmap *_metalNorth;

    QPixmap *_metalSouth;

    QPixmap *_metalEast;

    QPixmap *_metalWest;

    QPixmap *_neutralNorth;

    QPixmap *_neutralSouth;

    QPixmap *_neutralEast;

    QPixmap *_neutralWest;

    QPixmap ** _walls;

};

#endif // IMAGEHANDLER_H

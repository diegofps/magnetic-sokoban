#ifndef PLATEPENCIL_H
#define PLATEPENCIL_H

#include "mappencil.h"

class PlatePencil : public MapPencil
{

public:

    PlatePencil(const QPixmap & pixmap, MapObject::Material material, MapObject::Direction direction);

    QString name() const;

    MapObject paint(const MapObject &) const;

private:

    MapObject::Material _material;

    MapObject::Direction _direction;

};

#endif // PLATEPENCIL_H

#ifndef WALLPENCIL_H
#define WALLPENCIL_H

#include "mappencil.h"

class WallPencil : public MapPencil
{

public:

    WallPencil(const QPixmap & pixmap, const MapObject::Material material, bool isRigid);

    QString name() const;

    MapObject paint(const MapObject &) const;

private:

    MapObject::Material _material;

    bool _isRigid;

};

#endif // WALLPENCIL_H

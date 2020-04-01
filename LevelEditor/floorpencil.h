#ifndef FLOORPENCIL_H
#define FLOORPENCIL_H

#include "mappencil.h"

class FloorPencil : public MapPencil
{

public:

    FloorPencil(const QPixmap &pixmap, bool isObjective);

    QString name() const;

    MapObject paint(const MapObject &) const;

private:

    bool _isObjective;

};

#endif // FLOORPENCIL_H

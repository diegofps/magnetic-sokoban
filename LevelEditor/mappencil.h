#ifndef MAPPENCIL_H
#define MAPPENCIL_H

#include <QString>
#include <QPixmap>
#include "mapobject.h"

class MapPencil
{

public:

    MapPencil(const QPixmap & pixmap);

    virtual QPixmap pixmap() const;

    virtual QString name() const = 0;

    virtual MapObject paint(const MapObject& mapObject) const = 0;

private:

    QPixmap _pixmap;

};

#endif // MAPPENCIL_H

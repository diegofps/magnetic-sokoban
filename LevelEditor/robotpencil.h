#ifndef ROBOTPENCIL_H
#define ROBOTPENCIL_H

#include "mappencil.h"

class RobotPencil : public MapPencil
{

public:

    RobotPencil(const QPixmap & pixmap, MapObject::Direction direction);

    QString name() const;

    MapObject paint(const MapObject &) const;

private:

    MapObject::Direction _direction;

};

#endif // ROBOTPENCIL_H

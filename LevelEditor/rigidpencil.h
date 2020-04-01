#ifndef RIGIDPENCIL_H
#define RIGIDPENCIL_H

#include "mappencil.h"

class RigidPencil : public MapPencil
{

public:

    RigidPencil(const QPixmap & pixmap, bool isRigid);

    QString name() const;

    MapObject paint(const MapObject &) const;

private:

    bool _isRigid;

};

#endif // RIGIDPENCIL_H

#include "mappencil.h"
#include <QPixmap>

MapPencil::MapPencil(const QPixmap & pixmap) : _pixmap(pixmap)
{

}

QPixmap MapPencil::pixmap() const
{
    return _pixmap;
}

#include "qgameimage.h"

QGameImage::QGameImage(QPixmap pixmap) : _pixmap(pixmap) { }

int QGameImage::width()
{
    return _pixmap.width();
}

int QGameImage::height()
{
    return _pixmap.height();
}

QPixmap QGameImage::pixmap()
{
    return _pixmap;
}

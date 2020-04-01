#ifndef QGAMEIMAGE_H
#define QGAMEIMAGE_H

#include <QPixmap>
#include "image.h"

class QGameImage : public Image
{

public:

    QGameImage(QPixmap pixmap);

    int width();

    int height();

    QPixmap pixmap();

private:

    QPixmap _pixmap;

};

#endif // QGAMEIMAGE_H

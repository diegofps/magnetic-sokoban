#include "qgamemotionbackground.h"
#include "graphics.h"
#include "image.h"
#include <cmath>
#include "viewport.h"

QGameMotionBackground::QGameMotionBackground(Image * image, const float xSpeed, const float ySpeed) :
    MotionBackground(image, xSpeed, ySpeed),
    _xOffset(0), _yOffset(0)
{ }

void QGameMotionBackground::onPaint(const Viewport & viewport, Graphics *g)
{
    int xStart = ( -( (viewport.x() + (int)_xOffset) % image()->width()) - image()->width()) % image()->width();
    int yStart = ( -( (viewport.y() + (int)_yOffset) % image()->height()) - image()->height()) % image()->height();

    for (int x = xStart; x < viewport.width(); x += image()->width())
        for (int y = yStart; y < viewport.height(); y += image()->height())
            g->drawImage(image(), x, y);

    _xOffset = fmod( _xOffset + xSpeed() + image()->width(), image()->width() );
    _yOffset = fmod( _yOffset + ySpeed() + image()->height(), image()->height() );
}


void QGameMotionBackground::onModalPaint(const Viewport & viewport, Graphics *g)
{
    int xStart = ( -( (viewport.x() + (int)_xOffset) % image()->width()) - image()->width()) % image()->width();
    int yStart = ( -( (viewport.y() + (int)_yOffset) % image()->height()) - image()->height()) % image()->height();

    for (int x = xStart; x < viewport.width(); x += image()->width())
        for (int y = yStart; y < viewport.height(); y += image()->height())
            g->drawImage(image(), x, y);
}

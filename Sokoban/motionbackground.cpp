#include "motionbackground.h"
#include "viewport.h"
#include "image.h"
#include "graphics.h"
#include "math.h"

MotionBackground::MotionBackground(Image * image, const float xSpeed, const float ySpeed) :
    Background(image), _xSpeed(xSpeed), _ySpeed(ySpeed), _xOffset(0), _yOffset(0)
{

}

float MotionBackground::xSpeed()
{
    return _xSpeed;
}

float MotionBackground::ySpeed()
{
    return _ySpeed;
}

void MotionBackground::onPaint(const Viewport &viewport, Graphics *g)
{
    int xStart = ( -( (viewport.x() + (int)_xOffset) % image()->width()) - image()->width()) % image()->width();
    int yStart = ( -( (viewport.y() + (int)_yOffset) % image()->height()) - image()->height()) % image()->height();

    for (int x = xStart; x < viewport.width(); x += image()->width())
        for (int y = yStart; y < viewport.height(); y += image()->height())
            g->drawImage(image(), x, y);

    _xOffset = fmod( _xOffset + xSpeed() + image()->width(), image()->width() );
    _yOffset = fmod( _yOffset + ySpeed() + image()->height(), image()->height() );
}

void MotionBackground::onModalPaint(const Viewport &viewport, Graphics *g)
{
    int xStart = ( -( (viewport.x() + (int)_xOffset) % image()->width()) - image()->width()) % image()->width();
    int yStart = ( -( (viewport.y() + (int)_yOffset) % image()->height()) - image()->height()) % image()->height();

    for (int x = xStart; x < viewport.width(); x += image()->width())
        for (int y = yStart; y < viewport.height(); y += image()->height())
            g->drawImage(image(), x, y);
}

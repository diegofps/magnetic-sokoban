#ifndef MOTIONBACKGROUND_H
#define MOTIONBACKGROUND_H

#include "background.h"

class Image;

class MotionBackground : public Background
{

public:

    MotionBackground(Image * image, const float xSpeed=0.0, const float ySpeed=0.0);

    void onPaint(const Viewport &viewport, Graphics *g);

    void onModalPaint(const Viewport &viewport, Graphics *g);

    float xSpeed();

    float ySpeed();

private:

    float _xSpeed;

    float _ySpeed;

    float _xOffset;

    float _yOffset;

};

#endif // MOTIONBACKGROUND_H

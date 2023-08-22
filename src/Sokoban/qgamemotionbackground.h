#ifndef QGAMEMOTIONBACKGROUND_H
#define QGAMEMOTIONBACKGROUND_H

#include "motionbackground.h"

class Viewport;

class QGameMotionBackground : public MotionBackground
{

public:

    QGameMotionBackground(Image * image, const float xSpeed, const float ySpeed);

    void onPaint(const Viewport & viewport, Graphics *g);

    void onModalPaint(const Viewport & viewport, Graphics *g);

private:

    float _xOffset;

    float _yOffset;

};

#endif // QGAMEMOTIONBACKGROUND_H

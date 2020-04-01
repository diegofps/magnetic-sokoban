#ifndef GRAPHICS_H
#define GRAPHICS_H

class Image;
class MotionBackground;

#include "viewport.h"

class Graphics
{

public:

    Graphics() { }

    virtual ~Graphics() { }

    virtual Image *
    newImage(const char *filePath) = 0;

    virtual MotionBackground *
    newMotionBackground(Image * image, const float xSpeed, const float ySpeed) = 0;

    virtual void
    drawImage(Image * image, int x, int y) = 0;

    virtual void
    drawSubImage(Image * image, int x, int y, int imX, int imY, int imW, int imH) = 0;

};

#endif // GRAPHICS_H

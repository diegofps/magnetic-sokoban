#ifndef BACKGROUND_H
#define BACKGROUND_H

class Graphics;
class Image;
class Viewport;

class Background
{

public:

    Background(Image * image);

    Image * image();

    virtual void onPaint(const Viewport & viewport, Graphics *g) = 0;

    virtual void onModalPaint(const Viewport & viewport, Graphics *g) = 0;

private:

    Image *_image;

};

#endif // BACKGROUND_H

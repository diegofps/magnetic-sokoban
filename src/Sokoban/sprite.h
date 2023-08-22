#ifndef SPRITE_H
#define SPRITE_H

class Image;
class Graphics;

class Sprite
{

public:

    Sprite(Image *image, const unsigned int frames, const unsigned int columns, const unsigned int rows, const unsigned int delay);

    ~Sprite();

    void
    draw(Graphics *g, const int x, const int y);

    void
    drawFrame(Graphics *g, const unsigned int frame, const int x, const int y);

    int
    frame();

    int
    width();

    int
    height();

private:

    Image *_image;

    unsigned int _frame;

    unsigned int _frames;

    unsigned int _columns;

    float _width;

    float _height;

    unsigned int _delay;

};

#endif // SPRITE_H

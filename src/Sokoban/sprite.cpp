#include "sprite.h"
#include "image.h"
#include "graphics.h"
#include <cstdlib>

Sprite::Sprite(Image *image, const unsigned int frames, const unsigned int columns, const unsigned int rows, const unsigned int delay) :
    _image(image), _frame(0), _frames(frames), _columns(columns), _delay(delay + 1)
{
    _width = (float) _image->width() / columns;
    _height = (float) _image->height() / rows;
}

Sprite::~Sprite()
{
    if (_image != NULL)
        delete _image;
}

void
Sprite::draw(Graphics *g, const int x, const int y)
{
    int j = (_frame / _delay) % _columns;
    int i = (_frame / _delay) / _columns;

    int imX = (int) (j * _width);
    int imY = (int) (i * _height);

    g->drawSubImage(_image, x, y, imX, imY, (int) _width, (int) _height);

    _frame = (_frame + 1) % (_delay * _frames);
}

void
Sprite::drawFrame(Graphics *g, const unsigned int frame, const int x, const int y)
{
    if (frame >= _frames) return;

    int imX = (int) ((frame % _columns) * _width);
    int imY = (int) ((frame / _columns) * _height);

    g->drawSubImage(_image, x, y, imX, imY, (int) _width, (int) _height);
}

int
Sprite::width()
{
    return (int) _width;
}

int
Sprite::height()
{
    return (int) _height;
}

int Sprite::frame()
{
    return _frame / _delay;
}

#ifndef VIEWPORT_H
#define VIEWPORT_H

class Viewport
{

public:

    Viewport() : _x(0), _y(0), _width(800), _height(600) { }

    int x() const { return _x; }

    int y() const { return _y; }

    int width() const { return _width; }

    int height() const { return _height; }

    void x(int x) { _x = x; }

    void y(int y) { _y = y; }

    //void width(int width) { _width = width; }

    //void height(int height) { _height = height; }

private:

    int _x;

    int _y;

    int _width;

    int _height;

};

#endif // VIEWPORT_H

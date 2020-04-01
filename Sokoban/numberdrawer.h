#ifndef NUMBERDRAWER_H
#define NUMBERDRAWER_H

#include <cstdio>
#include "sprite.h"

class Sprite;

class NumberDrawer
{

public:

    NumberDrawer(Sprite * numbers) : _numbers(numbers) {
        _buffer[0] = '\0';
    }

    void number(int number) {
        sprintf(_buffer, "%d", number);
    }

    int width() const {
        int i;
        for (i=0;_buffer[i] != '\0'; ++i);
        return i * _numbers->width();
    }

    int height() const {
        return _numbers->height();
    }

    void draw(Graphics *g, int x, const int y) {
        for (int i=0; _buffer[i] != '\0' && i < 10; ++i) {
            if (_buffer[i] >= '0' && _buffer[i] <= '9') {
                _numbers->drawFrame(g, _buffer[i] - '0', x, y);
                x += _numbers->width();
            }
        }
    }

private:

    Sprite *_numbers;

    char _buffer[10];

};


#endif // NUMBERDRAWER_H

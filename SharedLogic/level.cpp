#include "level.h"

Level::Level(const std::string& name, int sizeX, int sizeY) :
    _name(name), _sizeX(sizeX), _sizeY(sizeY)
{
    buffer = new Object*[sizeX * sizeY];

    for (int j=0; j<sizeY; ++j)
        for (int i=0; i< sizeX; ++i)
            buffer[i * sizeY + j] = NULL;
}

std::string Level::name() const
{
    return _name;
}

int Level::sizeX()
{
    return _sizeX;
}

int Level::sizeY()
{
    return _sizeY;
}

void Level::name(const std::string name)
{
    _name = name;
}

void Level::sizeX(const int sizeX) {
    _sizeX = sizeX;
}

void Level::sizeY(const int sizeY)
{
    _sizeY = sizeY;
}

Object * Level::at(const int x, const int y)
{
    if (x < 0 || y << 0 || x >= sizeX() || y >= sizeY())
        return NULL;

    return buffer[y * sizeY() + x];
}

void Level::put(Object * object, const int x, const int y)
{
    if (x < 0 || y << 0 || x >= sizeX() || y >= sizeY())
        return;

    buffer[y * sizeY() + x] = object;
}

#include "mapmemento.h"
#include "mapobject.h"

MapMemento::MapMemento(std::string name, int width, int height,
                       int stepsForGold, int stepsForSilver, int stepsForBronze,
                       MapObject *buffer) :
    _name(name), _width(width), _height(height),
    _stepsForGold(stepsForGold), _stepsForSilver(stepsForSilver), _stepsForBronze(stepsForBronze)
{
    _buffer = new MapObject[_width * _height];

    for (int i=0;i<_width*_height;++i)
        _buffer[i] = buffer[i];
}

MapMemento::~MapMemento()
{
    delete [] _buffer;
}

std::string MapMemento::name()
{
    return _name;
}

int MapMemento::width()
{
    return _width;
}

int MapMemento::height()
{
    return _height;
}

MapObject * MapMemento::buffer()
{
    return _buffer;
}

int MapMemento::stepsForGold()
{
    return _stepsForGold;
}

int MapMemento::stepsForSilver()
{
    return _stepsForSilver;
}

int MapMemento::stepsForBronze()
{
    return _stepsForBronze;
}

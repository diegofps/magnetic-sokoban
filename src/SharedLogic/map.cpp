#include "map.h"

Map::Map(std::string name, int w, int h, int stepsForGold, int stepsForSilver, int stepsForBronze) :
    _name(name), _width(w), _height(h),
    _stepsForGold(stepsForGold), _stepsForSilver(stepsForSilver), _stepsForBronze(stepsForBronze)
{
    _buffer = new MapObject[w * h];
}

Map::Map(MapMemento *memento)
{
    _buffer = NULL;
    this->memento(memento);
}

Map::~Map()
{
    delete [] _buffer;
}

MapObject Map::at(int x, int y)
{
    if (x < 0 || y < 0 || x >= _width || y >= _height)
        return MapObject();

    return _buffer[y * _width + x];
}

void Map::put(const MapObject &obj, int x, int y)
{
    if (x < 0 || y < 0 || x >= _width || y >= _height)
        return;

    _buffer[y * _width + x] = obj;
}

void Map::resizeTo(int width, int height)
{
    if (width == _width && height == _height) return;

    MapObject *newBuffer = new MapObject[width * height];

    for (int x=0;x<width && x<_width;++x)
        for (int y=0;y<height && y<_height;++y)
            newBuffer[y*width + x] = _buffer[y*_width + x];

    delete [] _buffer;

    _buffer = newBuffer;
    _width = width;
    _height = height;
}

void Map::update(std::string name, int width, int height, int stepsForGold, int stepsForSilver, int stepsForBronze)
{
    _name = name;
    resizeTo(width, height);
    _stepsForGold = stepsForGold;
    _stepsForSilver = stepsForSilver;
    _stepsForBronze = stepsForBronze;
}

MapMemento * Map::memento()
{
    return new MapMemento(_name, _width, _height, _stepsForGold, _stepsForSilver, _stepsForBronze, _buffer);
}

void Map::memento(MapMemento * memento)
{
    _name = memento->name();
    _width = memento->width();
    _height = memento->height();
    _stepsForGold = memento->stepsForGold();
    _stepsForSilver = memento->stepsForSilver();
    _stepsForBronze = memento->stepsForBronze();

    if (_buffer != NULL)
        delete [] _buffer;

    _buffer = new MapObject[_width * _height];

    for (int i=0;i<_width*_height;++i)
        _buffer[i] = memento->buffer()[i];
}

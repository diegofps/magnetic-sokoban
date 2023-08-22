#ifndef MAPMEMENTO_H
#define MAPMEMENTO_H

#include <string>

class MapObject;

class MapMemento
{

public:

    MapMemento(std::string name, int width, int height, int stepsForGold, int stepsForSilver, int stepsForBronze, MapObject *buffer);

    ~MapMemento();

    std::string name();

    int width();

    int height();

    int stepsForGold();

    int stepsForSilver();

    int stepsForBronze();

    MapObject * buffer();

private:

    std::string _name;

    int _width;

    int _height;

    int _stepsForGold;

    int _stepsForSilver;

    int _stepsForBronze;

    MapObject * _buffer;

};

#endif // MAPMEMENTO_H

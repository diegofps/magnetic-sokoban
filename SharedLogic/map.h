#ifndef MAP_H
#define MAP_H

#include <cstdlib>
#include <string>
#include "mapmemento.h"
#include "mapobject.h"

class Map
{

public:

    Map(std::string name, int w, int h, int stepsForGold, int stepsForSilver, int stepsForBronze);

    Map(MapMemento *memento);

    ~Map();


    std::string name() { return _name; }

    int height() { return _height; }

    int width() { return _width; }

    int stepsForGold() { return _stepsForGold; }

    int stepsForSilver() { return _stepsForSilver; }

    int stepsForBronze() { return _stepsForBronze; }


    void update(std::string name, int width, int height, int stepsForGold, int stepsForSilver, int stepsForBronze);

    MapObject at(int x, int y);

    void put(const MapObject &obj, int x, int y);

    MapMemento * memento();

    void memento(MapMemento * memento);

private:

    void resizeTo(int width, int height);

    std::string _name;

    int _width;

    int _height;

    int _stepsForGold;

    int _stepsForSilver;

    int _stepsForBronze;

    MapObject *_buffer;

};

#endif // MAP_H

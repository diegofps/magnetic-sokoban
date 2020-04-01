#ifndef MAPPACK_H
#define MAPPACK_H

#include "map.h"
#include <cstdio>
#include <vector>
#include <string>

class MapPack
{

private:

    static const int VERSION_CODE = 1024 | 4;

public:

    MapPack();

    ~MapPack();

    Map * newMap(std::string name, int width, int height, int stepsForGold, int stepsForSilver, int stepsForBronze);

    std::vector<Map*> * all();

    Map * at(int index);

    Map * removeAt(int index);

    void newAt(int index, MapMemento *memento);

    void removeLast();

    void moveUp(int index);

    void moveDown(int index);

    bool importFrom(const char *filePath);

    bool importFrom(std::istream *is);

    bool exportTo(const char *filePath);

    //bool exportTo(std::ostream *os);

private:

    std::vector<Map*> _maps;
};

#endif // MAPPACK_H

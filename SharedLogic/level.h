#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "object.h"

class Level
{
public:
    Level(const std::string& name, int sizeX, int sizeY);

    std::string name() const;
    int sizeX();
    int sizeY();

    void name(const std::string name);
    void sizeX(const int sizeX);
    void sizeY(const int sizeY);

    Object * at(const int x, const int y);
    void put(Object * object, const int x, const int y);

private:
    Object ** buffer;
    std::string _name;
    int _sizeX;
    int _sizeY;
};

#endif // LEVEL_H

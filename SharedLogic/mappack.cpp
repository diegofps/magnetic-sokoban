#include "mappack.h"
#include <iostream>
#include <fstream>

MapPack::MapPack()
{

}

MapPack::~MapPack()
{
    for(std::vector<Map*>::iterator it=_maps.begin();it != _maps.end();++it)
        delete (*it);
}

Map * MapPack::newMap(std::string name, int width, int height, int stepsForGold, int stepsForSilver, int stepsForBronze)
{
    Map *map = new Map(name, width, height, stepsForGold, stepsForSilver, stepsForBronze);
    _maps.push_back(map);

    return map;
}

std::vector<Map*> * MapPack::all()
{
    return &_maps;
}

Map * MapPack::at(int index)
{
    if (index < 0 || index >= (int)_maps.size())
        return NULL;

    return _maps.at(index);
}

Map * MapPack::removeAt(int index)
{
    Map *map = at(index);
    _maps.erase(_maps.begin() + index);
    return map;
}

void MapPack::newAt(int index, MapMemento *memento)
{
    _maps.insert(_maps.begin() + index, new Map(memento));
}

void MapPack::removeLast()
{
    if (_maps.size() == 0) return;

    _maps.pop_back();
}

void MapPack::moveUp(int index)
{
    if (index <= 0 || index >= (int)_maps.size())
        return;

    Map *level = _maps.at(index);
    _maps.erase(_maps.begin() + index);
    _maps.insert(_maps.begin() + index - 1, level);
}

void MapPack::moveDown(int index)
{
    if (index < 0 || index >= (int)_maps.size() - 1)
        return;

    Map *level = _maps.at(index);
    _maps.erase(_maps.begin() + index);
    _maps.insert(_maps.begin() + index + 1, level);
}

bool MapPack::exportTo(const char * path)
{
    FILE *f = fopen(path, "w+");
    if (!f) return false;

    int versionCode = VERSION_CODE;
    fwrite(&versionCode, sizeof(int), 1, f);

    int number;

    number = _maps.size();
    fwrite(&number, sizeof(int), 1, f);

    for (std::vector<Map*>::iterator it = _maps.begin(); it != _maps.end(); ++it) {

        std::string name = (*it)->name();
        int width = (*it)->width();
        int height = (*it)->height();
        int stepsForGold = (*it)->stepsForGold();
        int stepsForSilver = (*it)->stepsForSilver();
        int stepsForBronze = (*it)->stepsForBronze();

        number = name.length();

        fwrite(&number, sizeof(int), 1, f);
        fwrite(name.c_str(), sizeof(char), number, f);
        fwrite(&width, sizeof(int), 1, f);
        fwrite(&height, sizeof(int), 1, f);
        fwrite(&stepsForGold, sizeof(int), 1, f);
        fwrite(&stepsForSilver, sizeof(int), 1, f);
        fwrite(&stepsForBronze, sizeof(int), 1, f);

        MapObject mapObject;
        for (int x=0;x<width;++x) {
            for (int y=0;y<height;++y) {
                mapObject = (*it)->at(x, y);
                fwrite(&mapObject, sizeof(MapObject), 1, f);
            }
        }

    }

    fclose(f);

    return true;

}

bool MapPack::importFrom(const char * filePath)
{
    std::ifstream ifs(filePath, std::ios::in | std::ios::binary);
    if (ifs.is_open()) return importFrom(&ifs);
    else return false;
}

bool MapPack::importFrom(std::istream *is)
{
    int versionCode;

    is->read((char*)&versionCode, sizeof(int));
    if (is->fail() || versionCode != VERSION_CODE) return false;

    int maps;

    is->read((char*)&maps, sizeof(int));
    if (is->fail()) return false;

    int bufferSize = 1024;
    char *buffer = (char*) malloc(sizeof(char) * bufferSize);
    if (!buffer) return false;

    for(int i=0;i<maps;++i) {

        int nameLen;
        int width;
        int height;
        int stepsForGold;
        int stepsForSilver;
        int stepsForBronze;

        is->read((char*)&nameLen, sizeof(int));
        if (is->fail()) { free(buffer); return false; }

        if (nameLen + 1 > bufferSize) {
            bufferSize = nameLen + 1;
            buffer = (char*) realloc(buffer, sizeof(char) * bufferSize);
            if (!buffer) return false;
        }

        buffer[nameLen] = '\0';

        is->read(buffer, nameLen);
        if (is->fail()) { free(buffer); return false; }

        is->read((char*)&width, sizeof(int));
        if (is->fail()) { free(buffer); return false; }

        is->read((char*)&height, sizeof(int));
        if (is->fail()) { free(buffer); return false; }

        is->read((char*)&stepsForGold, sizeof(int));
        if (is->fail()) { free(buffer); return false; }

        is->read((char*)&stepsForSilver, sizeof(int));
        if (is->fail()) { free(buffer); return false; }

        is->read((char*)&stepsForBronze, sizeof(int));
        if (is->fail()) { free(buffer); return false; }

        Map *map = newMap(buffer, width, height, stepsForGold, stepsForSilver, stepsForBronze);

        MapObject mapObject;
        for (int x=0;x<width;++x) {
            for (int y=0;y<height;++y) {
                is->read((char*)&mapObject, sizeof(MapObject));
                if (is->fail()) { free(buffer); return false; }

                map->put(mapObject, x, y);
            }
        }

    }

    free(buffer);

    return true;
}

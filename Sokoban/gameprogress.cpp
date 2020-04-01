#include "gameprogress.h"
#include <iostream>
#include <fstream>

GameProgress::GameProgress() :
    _stars(NULL), _starsLength(0)
{
    loadFrom("progress.save");
}

GameProgress::~GameProgress()
{
    saveTo("progress.save");
}

GameProgress::Star GameProgress::star(const unsigned int level)
{
    if (level >= _starsLength)
        reallocate(level+1);

    return _stars[level];
}

void GameProgress::putStar(const GameProgress::Star s, const unsigned int l)
{
    if (l >= _starsLength)
        reallocate(l + 1);

    if (isBetter(s, _stars[l]))
        _stars[l] = s;
}

bool GameProgress::isBetter(const GameProgress::Star s1, const GameProgress::Star s2)
{
    return int(s1) > int(s2);
}

void GameProgress::saveTo(const char *filePath)
{
    std::ofstream file(filePath, std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file.write((char*)&_starsLength, sizeof(_starsLength));
        for (int i=0; i<(int)_starsLength; ++i)
            file.write((char*)&_stars[i], sizeof(GameProgress::Star));
    } else {
        std::cout << "Could not save game progress" << std::endl;
    }
}

void GameProgress::loadFrom(const char *filePath)
{
    std::ifstream file(filePath, std::ios::in | std::ios::binary);
    if (!file.is_open()) return;

    int size;

    file.read((char*)&size, sizeof(size));
    if (file.fail()) return;

    reallocate(size);

    GameProgress::Star star;
    for (int i=0; i<size; ++i) {
        file.read((char*)&star, sizeof(GameProgress::Star));

        if (file.fail()) {
            delete _stars;
            _stars = NULL;
            _starsLength = 0;
            break;
        }

        putStar(star, i);
    }

}

void GameProgress::reallocate(const int size)
{
    GameProgress::Star *stars = new GameProgress::Star[size];
    int i;

    for(i=0; i<(int)_starsLength; ++i) stars[i] = _stars[i];
    for(;i<size;++i) stars[i] = GameProgress::NONE;
    if (_stars != NULL) delete [] _stars;

    _stars = stars;
    _starsLength = size;
}

bool GameProgress::isLocked(const unsigned int level)
{
    if (level == 0)
        return false;

    return star(level - 1) == GameProgress::NONE;
}

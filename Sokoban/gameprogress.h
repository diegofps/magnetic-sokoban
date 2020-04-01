#ifndef GAMEPROGRESS_H
#define GAMEPROGRESS_H

class GameProgress
{

public:

    enum Star { GOLD = 4, SILVER = 3, BRONZE = 2, MISSING = 1, NONE = 0 };

    GameProgress();

    ~GameProgress();

    Star star(const unsigned int level);

    void putStar(const GameProgress::Star star, const unsigned int level);

    bool isLocked(const unsigned int level);

    bool isBetter(const GameProgress::Star s1, const GameProgress::Star s2);

private:

    void saveTo(const char * filePath);

    void loadFrom(const char * filePath);

    void reallocate(const int size);

private:

    Star *_stars;

    unsigned int _starsLength;

};

#endif // GAMEPROGRESS_H

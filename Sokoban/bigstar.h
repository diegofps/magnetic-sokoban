#ifndef BIGSTAR_H
#define BIGSTAR_H

#include "object.h"

class SpritesHandler;

class BigStar : public Object
{

private:

    static const int DELAY = 1;

public:

    BigStar(Engine *engine, SpritesHandler *spritesHandler, Object *window, const int robotSteps, const int stepsForGold, const int stepsForSilver, const int stepsForBronze);

    virtual void draw(const Viewport &viewport, Graphics *g);

private:

    SpritesHandler *_spritesHandler;

    Object *_window;

    int _showSteps;

    int _robotSteps;

    int _stepsForGold;

    int _stepsForSilver;

    int _stepsForBronze;

};

#endif // BIGSTAR_H

#ifndef BIGFOOT_H
#define BIGFOOT_H

#include "object.h"

class SpritesHandler;

class BigFoot : public Object
{

public:

    BigFoot(Engine *engine, Object *window, SpritesHandler *spritesHandler, const int robotSteps, const int stepsForGold, const int stepsForSilver, const int stepsForBronze);

    virtual void draw(const Viewport &viewport, Graphics *g);

private:

    Object *_window;

    SpritesHandler *_spritesHandler;

    int _robotSteps;

    int _stepsForGold;

    int _stepsForSilver;

    int _stepsForBronze;

};

#endif // BIGFOOT_H

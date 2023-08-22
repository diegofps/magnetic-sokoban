#ifndef FLOOR_H
#define FLOOR_H

#include "object.h"

class SpritesHandler;

class Floor :public Object
{

public:

    Floor(Engine *engine, bool isObjective, SpritesHandler *spritesHandler);

};

#endif // FLOOR_H

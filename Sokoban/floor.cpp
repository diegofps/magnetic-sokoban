#include "floor.h"
#include "spriteshandler.h"

Floor::Floor(Engine *engine, bool isObjective, SpritesHandler *spritesHandler) : Object(engine)
{
    if (isObjective)
        sprite(spritesHandler->floorObjective());
    else
        sprite(spritesHandler->floor());
}

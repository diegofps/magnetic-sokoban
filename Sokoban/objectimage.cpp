#include "objectimage.h"
#include "engine.h"
#include "graphics.h"
#include "sprite.h"

ObjectImage::ObjectImage(Engine *engine, const char * filePath)
    : Object(engine)
{
    sprite(new Sprite(engine->graphics()->newImage(filePath), 1, 1, 1, 0));
}

ObjectImage::ObjectImage(Engine *engine, Sprite * sprite)
    : Object(engine)
{
    this->sprite(sprite);
}

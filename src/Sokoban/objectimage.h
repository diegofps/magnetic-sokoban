#ifndef OBJECTIMAGE_H
#define OBJECTIMAGE_H

#include "object.h"

class Sprite;

class ObjectImage : public Object
{

public:

    ObjectImage(Engine *engine, const char * filePath);

    ObjectImage(Engine *engine, Sprite * sprite);

};

#endif // OBJECTIMAGE_H

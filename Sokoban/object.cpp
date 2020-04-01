#include "object.h"
#include "graphics.h"
#include "viewport.h"
#include "sprite.h"

void Object::draw(const Viewport & viewport, Graphics *g)
{
    if (_sprite == NULL) return;

    int drawX = _x - viewport.x();
    int drawY = _y - viewport.y();

    _sprite->draw(g, drawX, drawY);
}

void Object::modalDraw(const Viewport & viewport, Graphics *g)
{
    if (_sprite == NULL) return;

    int drawX = _x - viewport.x();
    int drawY = _y - viewport.y();

    _sprite->drawFrame(g, _sprite->frame(), drawX, drawY);
}

int Object::width()
{
     return _sprite == NULL ? 0 : _sprite->width();
}

int Object::height()
{
    return _sprite == NULL ? 0 : _sprite->height();
}

bool Object::runWhenPaused()
{
    return false;
}

bool Object::runWhenNotPaused()
{
    return true;
}

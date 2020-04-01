#ifndef OBJECT_H
#define OBJECT_H

#include <cstdlib>

class Engine;
class Sprite;
class Graphics;
class Viewport;

class Object
{

public:

    Object(Engine *engine) : _engine(engine), _x(0), _y(0), _sprite(NULL), _visible(true) { }

    virtual ~Object() { }

    virtual void draw(const Viewport & viewport, Graphics * g);

    virtual void modalDraw(const Viewport & viewport, Graphics * g);

    virtual int width();

    virtual int height();

    virtual bool runWhenPaused();

    virtual bool runWhenNotPaused();


    int x() { return _x; }

    int y() { return _y; }

    Sprite * sprite() { return _sprite; }

    Engine * engine() { return _engine; }

    bool visible() { return _visible; }


    void x(int x) { _x = x; }

    void y(int y) { _y = y; }

    void sprite(Sprite *sprite) { _sprite = sprite; }

    void visible(bool visible) { _visible = visible; }

private:

    Engine *_engine;

    int _x;

    int _y;

    Sprite *_sprite;

    bool _visible;

};

#endif // OBJECT_H

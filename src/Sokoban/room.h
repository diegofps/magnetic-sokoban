#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <map>

#include "viewport.h"
#include "mouselistener.h"
#include "keylistener.h"

class Engine;
class Background;
class ViewportRefresher;
class StepListener;
class Object;
class Graphics;

class Room
{

public:

    Room(Engine *engine);

    Room(Engine *engine, Room *parent);

    virtual ~Room();


    virtual void onEnter();

    virtual void onLeave();

    virtual void onModalRoomClose(Room *modalRoom, int resultCode);


    Engine * engine();

    std::vector<Background*> * backgrounds();

    void addBackground(Background *bg);

    void addBackground(const char * filePath);

    void close(int resultCode);

    Room * parent();

    const Viewport & viewport();


    Room * modal();

    void modal(Room *modalRoom);


    void addObject(Object *object);

    void addObject(float weight, Object *object);

    void addMouseListener(MouseListener *listener);

    void addKeyListener(KeyListener *listener);

    void addStepListener(StepListener *listener);

    void setViewportRefresher(ViewportRefresher *refresher);

    void clear();


    void onDraw(Graphics *g);

    void onStep();

    void onViewportRefresher();

    void onMousePress(const MouseListener::Buttons buttons, const int x, const int y);

    void onMouseMove(const MouseListener::Buttons buttons, const int x, const int y, const int lastX, const int lastY);

    void onMouseRelease(const MouseListener::Buttons buttons, const int x, const int y);

    void onKeyPress(KeyListener::Key key);

    void onKeyRelease(KeyListener::Key key);


private:

    Engine *_engine;

    std::vector<Background*> _backgrounds;

    Room *_modalRoom;

    Room *_parent;

    std::multimap<float, Object*> _objects;

    std::vector<MouseListener*> _mouseListeners;

    std::vector<KeyListener*> _keyListeners;

    std::vector<StepListener*> _stepListeners;

    ViewportRefresher *_viewportRefresher;

    Viewport _viewport;

};

#endif // ROOM_H

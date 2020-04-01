#include "room.h"
#include "image.h"
#include "background.h"
#include "engine.h"
#include "graphics.h"
#include "motionbackground.h"
#include <cstdlib>
#include "viewportrefresher.h"
#include "helpers.h"
#include "steplistener.h"

Room::Room(Engine *engine) :
    _engine(engine), _modalRoom(NULL), _parent(NULL), _viewportRefresher(NULL)
{

}

Room::Room(Engine *engine, Room *parent) :
    _engine(engine), _modalRoom(NULL), _parent(parent), _viewportRefresher(NULL)
{

}

Room::~Room()
{

}

Engine *
Room::engine()
{
    return _engine;
}

void
Room::addBackground(Background *bg)
{
    _backgrounds.push_back(bg);
}

void
Room::addBackground(const char * filePath)
{
    Image *imgBackground = engine()->graphics()->newImage(filePath);
    Background *background = engine()->graphics()->newMotionBackground(imgBackground, 0, 0);
    addBackground(background);
}

void Room::onModalRoomClose(Room *, int)
{

}

Room * Room::modal()
{
    return _modalRoom;
}

void Room::modal(Room *modalRoom)
{
    _modalRoom = modalRoom;
}

void Room::close(int resultCode)
{
    engine()->closeCurrentModalRoom(resultCode);
}

Room * Room::parent()
{
    return _parent;
}

const Viewport & Room::viewport()
{
    return _viewport;
}

void Room::addObject(Object *object)
{
    addObject(0, object);
}

void Room::addObject(float weight, Object *object)
{
    _objects.insert(std::pair<float, Object*>(weight, object));
}

void Room::addMouseListener(MouseListener *listener)
{
    _mouseListeners.push_back(listener);
}

void Room::addKeyListener(KeyListener *listener)
{
    _keyListeners.push_back(listener);
}

void Room::addStepListener(StepListener *listener)
{
    _stepListeners.push_back(listener);
}

void Room::setViewportRefresher(ViewportRefresher *refresher)
{
    _viewportRefresher = refresher;
}

void Room::clear()
{
    std::multimap<float, Object*>::iterator it;
    for(it = _objects.begin(); it != _objects.end(); ++it)
        delete (*it).second;

    _objects.clear();
    _mouseListeners.clear();
    _keyListeners.clear();
    _stepListeners.clear();

    _viewportRefresher = NULL;
}

void Room::onDraw(Graphics *g)
{
    if (_modalRoom == NULL) {
        std::vector<Background*>::iterator it;
        for (it = backgrounds()->begin(); it != backgrounds()->end(); ++it)
            (*it)->onPaint(viewport(), g);

        std::multimap<float, Object*>::iterator itObj;
        for(itObj = _objects.begin(); itObj != _objects.end(); ++itObj)
            if ((*itObj).second->visible())
                (*itObj).second->draw(viewport(), g);
    }

    else {
        std::vector<Background*>::iterator it;
        for (it = backgrounds()->begin(); it != backgrounds()->end(); ++it)
            (*it)->onModalPaint(viewport(), g);

        std::multimap<float, Object*>::iterator itObj;
        for(itObj = _objects.begin(); itObj != _objects.end(); ++itObj)
            if ((*itObj).second->visible())
                (*itObj).second->modalDraw(viewport(), g);

        _modalRoom->onDraw(g);
    }
}

void Room::onStep()
{
    std::vector<StepListener*>::iterator it;
    for (it = _stepListeners.begin(); it != _stepListeners.end(); ++it)
        (*it)->onStep();
}

void Room::onViewportRefresher()
{
    if (_viewportRefresher != NULL)
        _viewportRefresher->refresh(_viewport);
}

void Room::onMousePress(const MouseListener::Buttons buttons, const int x, const int y)
{
    std::vector<MouseListener*>::iterator it;
    for(it = _mouseListeners.begin(); it != _mouseListeners.end(); ++it) {
        if ((*it)->visible()) {
            if (helpers::pointInsideBox(x, y, (*it)->x(), (*it)->y(), (*it)->width(), (*it)->height() )) {
                (*it)->onButtonPress(buttons, x, y);
            }
        }
    }
}

void Room::onMouseMove(const MouseListener::Buttons buttons, const int x, const int y, const int lastX, const int lastY)
{
    std::vector<MouseListener*>::iterator it;

    for(it = _mouseListeners.begin(); it != _mouseListeners.end(); ++it) {
        (*it)->onMouseMove(buttons, x, y, lastX, lastY);

        if (helpers::pointInsideBox( x, y, (*it)->x(), (*it)->y(), (*it)->width(), (*it)->height() )) {
            if ((*it)->visible())
                if (!helpers::pointInsideBox(lastX, lastY, (*it)->x(), (*it)->y(), (*it)->width(), (*it)->height() ))
                    (*it)->onMouseEnter(buttons, x, y);
        } else {
            if ((*it)->visible())
                if (helpers::pointInsideBox(lastX, lastY, (*it)->x(), (*it)->y(), (*it)->width(), (*it)->height() ))
                    (*it)->onMouseLeave(buttons, x, y);
        }
    }
}

void Room::onMouseRelease(const MouseListener::Buttons buttons, const int x, const int y)
{
    std::vector<MouseListener*>::iterator it;

    for(it = _mouseListeners.begin(); it != _mouseListeners.end(); ++it) {
        if ((*it)->visible()) {
            if (helpers::pointInsideBox(x, y, (*it)->x(), (*it)->y(), (*it)->width(), (*it)->height() )) {
                (*it)->onButtonRelease(buttons, x, y);
            }
        }
    }
}

std::vector<Background*> * Room::backgrounds()
{
    return &_backgrounds;
}

void Room::onKeyPress(KeyListener::Key key)
{
    std::vector<KeyListener*>::iterator it;

    for(it = _keyListeners.begin(); it != _keyListeners.end(); ++it)
        (*it)->onKeyPress(key);
}

void Room::onKeyRelease(KeyListener::Key key)
{
    std::vector<KeyListener*>::iterator it;

    for(it = _keyListeners.begin(); it != _keyListeners.end(); ++it)
        (*it)->onKeyRelease(key);
}

void Room::onEnter()
{

}

void Room::onLeave()
{

}

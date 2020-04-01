#ifndef ENGINE_H
#define ENGINE_H

class Room;
class MouseListener;
class KeyListener;
class StepListener;
class Object;
class Graphics;
class ViewportRefresher;

class Engine
{

public:

    virtual ~Engine() { }

    virtual void start() = 0;

    virtual void endGame() = 0;

    virtual void goTo(Room *room) = 0;

    virtual void closeCurrentModalRoom(int resultCode) = 0;

    virtual Graphics * graphics() = 0;

};

#endif // ENGINE_H

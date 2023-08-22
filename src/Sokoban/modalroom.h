#ifndef MODALROOM_H
#define MODALROOM_H

#include "room.h"

class Room;

class ModalRoom : public Room
{

public:

    ModalRoom(Engine *engine, Room *parent);

    void close(int resultCode);

private:

    Room * _parent;

};

#endif // MODALROOM_H

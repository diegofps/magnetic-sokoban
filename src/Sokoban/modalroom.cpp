#include "modalroom.h"
#include <cstdlib>

ModalRoom::ModalRoom(Engine *engine, Room *parent) :
    Room(engine),
    _parent(parent)
{

}

void ModalRoom::close(int resultCode)
{
    _parent->modal(NULL);
    _parent->onModalRoomClose(resultCode);
}

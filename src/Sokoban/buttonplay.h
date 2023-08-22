#ifndef BUTTONPLAY_H
#define BUTTONPLAY_H

class Engine;
class Room;

#include "button.h"

class ButtonPlay : public Button
{

public:

    ButtonPlay(Engine *engine, Room *nextRoom);

    void onClick(int buttons);

private:

    Room *_nextRoom;

};

#endif // BUTTONPLAY_H

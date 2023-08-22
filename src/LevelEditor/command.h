#ifndef COMMAND_H
#define COMMAND_H

#include "commandslistener.h"

class Command
{
public:

    virtual ~Command() { }

    virtual void execute() = 0;

    virtual void unexecute() = 0;

    virtual void setCommandsListener(CommandsListener *listener) = 0;
};

#endif // COMMAND_H

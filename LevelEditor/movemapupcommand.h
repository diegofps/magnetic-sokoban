#ifndef MOVEMAPUPCOMMAND_H
#define MOVEMAPUPCOMMAND_H

#include "command.h"
#include "mappack.h"
#include "commandslistener.h"

class MoveMapUpCommand : public Command
{
public:

    MoveMapUpCommand(int mapId, MapPack * mapPack);

    virtual ~MoveMapUpCommand() { }

    virtual void execute();

    virtual void unexecute();

    virtual void setCommandsListener(CommandsListener *listener);

private:

    int _mapId;

    MapPack *_mapPack;

    CommandsListener *_listener;
};

#endif // MOVEMAPUPCOMMAND_H

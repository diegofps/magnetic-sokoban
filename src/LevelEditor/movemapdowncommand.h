#ifndef MOVEMAPDOWNCOMMAND_H
#define MOVEMAPDOWNCOMMAND_H

#include "command.h"
#include "mappack.h"
#include "commandslistener.h"

class MoveMapDownCommand : public Command
{
public:

    MoveMapDownCommand(int mapId, MapPack * mapPack);

    virtual ~MoveMapDownCommand() { }

    virtual void execute();

    virtual void unexecute();

    virtual void setCommandsListener(CommandsListener *listener);

private:

    int _mapId;

    MapPack *_mapPack;

    CommandsListener *_listener;
};

#endif // MOVEMAPDOWNCOMMAND_H

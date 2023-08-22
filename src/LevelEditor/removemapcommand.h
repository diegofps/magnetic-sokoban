#ifndef REMOVEMAPCOMMAND_H
#define REMOVEMAPCOMMAND_H

#include "command.h"
#include "mapmemento.h"
#include "mappack.h"

class RemoveMapCommand : public Command
{

public:

    RemoveMapCommand(MapPack *mapPack, int mapId);

    virtual ~RemoveMapCommand();

    virtual void execute();

    virtual void unexecute();

    virtual void setCommandsListener(CommandsListener *listener);

private:

    MapPack *_mapPack;

    int _mapId;

    MapMemento * _memento;

    CommandsListener *_listener;
};

#endif // REMOVEMAPCOMMAND_H

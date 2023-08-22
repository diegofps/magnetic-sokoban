#include "removemapcommand.h"

RemoveMapCommand::RemoveMapCommand(MapPack *mapPack, int mapId) :
    _mapPack(mapPack), _mapId(mapId)
{
    _memento = _mapPack->at(_mapId)->memento();
}

RemoveMapCommand::~RemoveMapCommand()
{
    delete _memento;
}

void RemoveMapCommand::execute()
{
    delete _mapPack->removeAt(_mapId);

    if (_listener != NULL)
        _listener->onRemoveMap(_mapId);
}

void RemoveMapCommand::unexecute()
{
    _mapPack->newAt(_mapId, _memento);

    if (_listener != NULL)
        _listener->onAddMap(_mapId);
}

void RemoveMapCommand::setCommandsListener(CommandsListener *listener)
{
    _listener = listener;
}

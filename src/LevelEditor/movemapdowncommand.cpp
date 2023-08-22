#include "movemapdowncommand.h"

MoveMapDownCommand::MoveMapDownCommand(int mapId, MapPack * mapPack) :
    _mapId(mapId), _mapPack(mapPack) { }

void MoveMapDownCommand::execute()
{
    _mapPack->moveDown(_mapId);

    if (_listener != NULL)
        _listener->onMoveMap(_mapId + 1, _mapId);
}

void MoveMapDownCommand::unexecute()
{
    _mapPack->moveDown(_mapId + 1);

    if (_listener != NULL)
        _listener->onMoveMap(_mapId, _mapId + 1);
}

void MoveMapDownCommand::setCommandsListener(CommandsListener *listener)
{
    _listener = listener;
}

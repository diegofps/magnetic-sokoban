#include "movemapupcommand.h"

MoveMapUpCommand::MoveMapUpCommand(int mapId, MapPack * mapPack) :
    _mapId(mapId), _mapPack(mapPack) { }

void MoveMapUpCommand::execute()
{
    _mapPack->moveUp(_mapId);

    if (_listener != NULL)
        _listener->onMoveMap(_mapId - 1, _mapId);
}

void MoveMapUpCommand::unexecute()
{
    _mapPack->moveDown(_mapId - 1);

    if (_listener != NULL)
        _listener->onMoveMap(_mapId, _mapId - 1);
}

void MoveMapUpCommand::setCommandsListener(CommandsListener *listener)
{
    _listener = listener;
}

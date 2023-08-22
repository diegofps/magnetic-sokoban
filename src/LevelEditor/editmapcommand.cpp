#include "editmapcommand.h"

EditMapCommand::EditMapCommand(std::string name, int width, int height,
                               int stepsForGold, int stepsForSilver, int stepsForBronze,
                               MapPack *mapPack, int mapId) :
    _name(name), _width(width), _height(height),
    _stepsForGold(stepsForGold), _stepsForSilver(stepsForSilver), _stepsForBronze(stepsForBronze),
    _mapPack(mapPack), _mapId(mapId), _listener(NULL)
{
    _memento = _mapPack->at(_mapId)->memento();
}

EditMapCommand::~EditMapCommand()
{
    delete _memento;
}

void EditMapCommand::execute()
{
    _mapPack->at(_mapId)->update(_name, _width, _height, _stepsForGold, _stepsForSilver, _stepsForBronze);

    if (_listener != NULL)
        _listener->onEditMap(_mapId);
}

void EditMapCommand::unexecute()
{
    _mapPack->at(_mapId)->memento(_memento);

    if (_listener != NULL)
        _listener->onEditMap(_mapId);
}

void EditMapCommand::setCommandsListener(CommandsListener *listener)
{
    _listener = listener;
}

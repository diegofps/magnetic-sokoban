#include "addmapcommand.h"

AddMapCommand::AddMapCommand(std::string name, int width, int height,
                             int stepsForGold, int stepsForSilver, int stepsForBronze,
                             MapPack *mapPack) :
    _name(name), _width(width), _height(height),
    _stepsForGold(stepsForGold), _stepsForSilver(stepsForSilver), _stepsForBronze(stepsForBronze),
    _mapPack(mapPack)
{

}

void AddMapCommand::execute()
{
    _mapPack->newMap(_name, _width, _height, _stepsForGold, _stepsForSilver, _stepsForBronze);

    if (_listener != NULL)
        _listener->onAddMap(_mapPack->all()->size() - 1);
}

void AddMapCommand::unexecute()
{
    _mapPack->removeLast();

    if (_listener != NULL)
        _listener->onRemoveMap(_mapPack->all()->size() + 1);
}

void AddMapCommand::setCommandsListener(CommandsListener *listener)
{
    _listener = listener;
}

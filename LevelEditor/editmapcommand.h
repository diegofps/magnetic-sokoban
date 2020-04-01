#ifndef EDITMAPCOMMAND_H
#define EDITMAPCOMMAND_H

#include <string>
#include "mappack.h"
#include "command.h"
#include "mapmemento.h"
#include "commandslistener.h"

class EditMapCommand : public Command
{
public:

    EditMapCommand(std::string name, int width, int height, int stepsForGold, int stepsForSilver, int stepsForBronze, MapPack *mapPack, int mapId);

    ~EditMapCommand();

    virtual void execute();

    virtual void unexecute();

    virtual void setCommandsListener(CommandsListener *listener);

private:

    std::string _name;

    int _width;

    int _height;

    int _stepsForGold;

    int _stepsForSilver;

    int _stepsForBronze;

    MapPack *_mapPack;

    int _mapId;

    CommandsListener *_listener;

    MapMemento *_memento;
};

#endif // EDITMAPCOMMAND_H

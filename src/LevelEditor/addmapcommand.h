#ifndef ADDMAPCOMMAND_H
#define ADDMAPCOMMAND_H

#include "command.h"
#include "mappack.h"
#include "mainwindow.h"

class AddMapCommand : public Command
{

public:

    AddMapCommand(std::string name, int width, int height, int stepsForGold, int stepsForSilver, int stepsForBronze, MapPack *mapPack);

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

    CommandsListener *_listener;
};

#endif // ADDMAPCOMMAND_H
